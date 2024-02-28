#include <firmware.h>
#include <Arduino.h>

//core 1
const int ins0 = 13;
const int data0 = 12;
const int jump0 = 11; //replace with out0 if not using jump pin
const int in0 = 10;

//core 2
const int ins1 = 9;
const int data1 = 8;
const int jump1 = 7; //replace with out1 if not using jump pin
const int in1 = 6;

int ram[512];
void init_all() {
  int ram[512] = {0};
  pinMode(ins0, OUTPUT);
  pinMode(ins1, OUTPUT);
  pinMode(data0, OUTPUT);
  pinMode(data1, OUTPUT);
  pinMode(jump0, INPUT); //replace with out0 if not using jump pin
  pinMode(jump1, INPUT); //replace with out1 if not using jump pin
  pinMode(in0, OUTPUT);
  pinMode(in1, OUTPUT);

  digitalWrite(ins0, LOW);
  digitalWrite(ins1, LOW);
  digitalWrite(data0, LOW);
  digitalWrite(data1, LOW);
  digitalWrite(in0, LOW);
  digitalWrite(in1, LOW);
}

int a0, b0, c0; //Core 1 registers
int a1, b1, c1; //Core 2 registers
int cf1, cf2; //carry flags
int zf1, zf2; //zero flags
int tmp1, tmp2, tmp3, tmp4; //core 1 temporary registers
int tmp5, tmp6, tmp7, tmp8; //core 2 temporary registers

int thread1::nand(int a0, int b0) {
  digitalWrite(ins0, HIGH);
  digitalWrite(data0, a0);
  digitalWrite(in0, b0);
  c0 = (!digitalRead(jump0)); //remove ! if not using jump pin and change jump0 to out0
  return c0;
}

int thread1::not_gate(int a0) {
  c0 = nand(a0, a0);
  return c0;
}

int thread1::or_gate(int a0, int b0) {
  c0 = nand((a0 = nand(a0, a0)), (b0 = nand(b0, b0)));
  return c0;
}

int thread1::nor_gate(int a0, int b0) {
  c0 = nand((a0 = nand(a0, a0)), (b0 = nand(b0, b0)));
  c0 = nand(c0, c0);
  return c0;
}

int thread1::and_gate(int a0, int b0) {
  c0 = nand(a0, b0);
  c0 = nand(c0, c0);
  return c0;
}

int thread1::xor_gate(int a0, int b0) {
  tmp1 = nand(a0, b0);
  a0 = nand(a0, tmp1);
  b0 = nand(b0, tmp1);
  c0 = nand(a0, b0);
  return c0;
}

int thread1::sto_reg(int a, int b) {
  switch (b) {
    case 0:
      ram[a] = a0;
      break;
    case 1:
      ram[a] = b0;
      break;
    case 2:
      ram[a] = c0;
      break;
  }
}

int thread1::sto(int a, int b) {
  ram[a] = b;
}

int thread2::nand(int a1, int b1) {
  digitalWrite(ins1, HIGH);
  digitalWrite(data1, a1);
  digitalWrite(in1, b1);
  c1 = (!digitalRead(jump1)); //remove ! if not using jump pin and change jump1 to out1
  return c1;
}

int thread2::not_gate(int a1) {
  c1 = nand(a1, a1);
  return c1;
}

int thread2::or_gate(int a1, int b1) {
  c1 = nand((a1 = nand(a1, a1)), (b1 = nand(b1, b1)));
  return c1;
}

int thread2::nor_gate(int a1, int b1) {
  c1 = nand((a1 = nand(a1, a1)), (b1 = nand(b1, b1)));
  c1 = nand(c1, c1);
  return c1;
}

int thread2::and_gate(int a1, int b1) {
  c1 = nand(a1, b1);
  c1 = nand(c1, c1);
  return c1;
}

int thread2::xor_gate(int a1, int b1) {
  tmp5 = nand(a1, b1);
  a1 = nand(a1, tmp5);
  b1 = nand(b1, tmp5);
  c1 = nand(a1, b1);
  return c1;
}

int thread2::sto_reg(int a, int b) {
  switch (b) {
    case 0:
      ram[a] = a1;
      break;
    case 1:
      ram[a] = b1;
      break;
    case 2:
      ram[a] = c1;
      break;
  }
}

int thread2::sto(int a, int b) {
  ram[a] = b;
}


thread1 t1;
thread2 t2;
