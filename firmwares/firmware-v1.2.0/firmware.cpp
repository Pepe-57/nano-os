#include "firmware.h"
#include "kernel.h"
#include "nano_os.h"
#include <Arduino.h>

//core 1
const int ins0 = 13;
const int jump0 = 12;
const int data0 = 11; //replace with out0 if not using jump pin
const int in0 = 10;

//core 2
const int ins1 = 9;
const int jump1 = 8;
const int data1 = 7; //replace with out1 if not using jump pin
const int in1 = 6;

int a0, b0, c0; //Core 1 registers
int a1, b1, c1; //Core 2 registers
int tmp1, tmp2, tmp3, tmp4; //core 1 temporary registers
int tmp5, tmp6, tmp7, tmp8; //core 2 temporary registers

/*
  TO DO:
  - Add free memory function, which will execute after the end of the program
*/

bool multicore = false;

int ram[RAM_SIZE]; 
/* Memory map:
  0x0000 - 0x0001 - io_driver
  0x0002 - 0x00FF - system, do not use for programs
  0x0100 - RAM_SIZE - free memory for programs
*/

int coreCount;
void firmware::dce() {
  Serial.println("--Direct Code Execution--");
  while (true) {
    while (!Serial.available());
    String input = Serial.readStringUntil('\n');
    int ins = input.toInt();
    if (input.length() == 0 || ins == 0 && input != "0") { //check for empty input
      continue;
    }
    Serial.print("Instruction: ");
    Serial.println(ins);
    Serial.print("Result: ");
    Serial.println(t1.diec(ins));
  }
}



int firmware::get_cpu_count() {
  return coreCount;
}

int firmware::get_ram_size() {
  return RAM_SIZE;
}

int firmware::free_mem(int addr1, int addr2) {
  for (int i = addr1; i <= addr2; i++) {
    ram[i] = 0;
  }
}


void firmware::init_core1() {
  digitalWrite(ins0, LOW);
  digitalWrite(data0, LOW);
  digitalWrite(in0, LOW);
  pinMode(ins0, OUTPUT);
  pinMode(data0, OUTPUT);
  pinMode(in0, OUTPUT);
  pinMode(jump0, INPUT); //replace with out0 if not using jump pin
}

void firmware::init_core2() {
  digitalWrite(ins1, LOW);
  digitalWrite(data1, LOW);
  digitalWrite(in1, LOW);
  pinMode(ins1, OUTPUT);
  pinMode(data1, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(jump1, INPUT); //replace with out1 if not using jump pin
}


void firmware::start() {
  Serial.begin(115200);
  Serial.println("Core count?");
  while (!Serial.available());
  coreCount = Serial.parseInt();
  if (coreCount == 1) {
    multicore = false;
    Serial.println("Core count set to 1");
  }
  else if (coreCount == 2) {
    multicore = true;
    Serial.println("Core count set to 2");
  } else {
    Serial.println("Invalid core count. Defaulting to 1 core.");
  }
  switch (multicore) {
    case true:
      init_core1();
      init_core2();
      break;
    case false:
      init_core1();
      break;
  }
  Serial.println("Select where to boot:");
  Serial.println("1.Nano-os 2.Direct Code Execution");
  while (!Serial.available());
  int sel = Serial.parseInt();
  if (sel == 1) {
    kernel.init_operating_system();
  } else if (sel == 2) {
    fw.dce();
  }
}


int firmware::get_registers() {
  Serial.print("A0: ");
  Serial.print(a0);
  Serial.print(" B0: ");
  Serial.print(b0);
  Serial.print(" C0: ");
  Serial.println(c0);
  Serial.print("A1: ");
  Serial.print(a1);
  Serial.print(" B1: ");
  Serial.print(b1);
  Serial.print(" C1: ");
  Serial.println(c1);
}

int thread1::nand(int a0, int b0) {
  digitalWrite(ins0, HIGH);
  digitalWrite(data0, a0);
  digitalWrite(in0, b0);
  delay(1);
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
  tmp1 = nand(a0, b0);
  c0 = nand(tmp1, tmp1);
  return c0;
}

int thread1::xor_gate(int a0, int b0) {
  tmp1 = nand(a0, b0);
  a0 = nand(a0, tmp1);
  b0 = nand(b0, tmp1);
  c0 = nand(a0, b0);
  return c0;
}

int thread1::sto_reg(int addr, int reg) {
  switch (reg) {
    case 0:
      ram[addr] = a0;
      break;
    case 1:
      ram[addr] = b0;
      break;
    case 2:
      ram[addr] = c0;
      break;
  }
}

int thread1::sto(int addr, int data) {
  ram[addr] = data;
}

//instruction format: in, data, instruction
int thread1::diec(int instruction) {
  tmp1 = instruction & 1;
  tmp2 = (instruction >> 1) & 1;
  tmp3 = (instruction >> 2) & 1;
  digitalWrite(ins0, tmp1);
  digitalWrite(data0, tmp2);
  digitalWrite(in0, tmp3);
  delay(1);
  if (tmp1 == 1) {
    c0 = (!digitalRead(jump0));
    return c0;
  }
  else if (tmp1 == 0) {
    c0 = (digitalRead(jump0));
    return c0;
  }
  return -1;
}



int thread2::nand(int a1, int b1) {
  if (!multicore) {
    return t1.nand(a1, b1);
  }
  digitalWrite(ins1, HIGH);
  digitalWrite(data1, a1);
  digitalWrite(in1, b1);
  delay(1);
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

int thread2::sto_reg(int addr, int reg) {
  switch (reg) {
    case 0:
      ram[addr] = a1;
      break;
    case 1:
      ram[addr] = b1;
      break;
    case 2:
      ram[addr] = c1;
      break;
  }
}

int thread2::sto(int addr, int data) {
  ram[addr] = data;
}
//instruction format: in, data, instruction
int thread2::diec(int instruction) {
  tmp5 = instruction & 1;
  tmp6 = (instruction >> 1) & 1;
  tmp7 = (instruction >> 2) & 1;
  digitalWrite(ins0, tmp5);
  digitalWrite(data0, tmp6);
  digitalWrite(in0, tmp7);
  delay(1);
  switch (tmp5)
  {
  case 1:
    c1 = (!digitalRead(jump1));
    return c1;
    break;
  case 0:
    c1 = (digitalRead(jump1));
    return c1;
    break;
  }
}

int nano_math::add16(int a, int b) {
  ram[260] = 0; //carry
  ram[261] = 0; //result

  for (int i = 0; i < 16; ++i) {
      ram[262] = (a >> i) & 1; //bit a
      ram[263] = (b >> i) & 1; //bit b

      ram[264] = t1.xor_gate(t1.xor_gate(ram[262], ram[263]), ram[260]);

      ram[260] = t1.or_gate(t1.and_gate(ram[262], ram[263]), t1.and_gate(t1.xor_gate(ram[262], ram[263]), ram[260]));

      ram[261] |= (ram[264] << i);
  }
  return ram[261];  
}

int nano_math::sub16(int a, int b) {
  ram[260] = 1; //carry
  ram[261] = 0; //result

  for (int i = 0; i < 16; ++i) {
      ram[262] = (a >> i) & 1; //bit a
      ram[263]= (t1.not_gate((b >> i) & 1)); //bit b

      ram[264] = t1.xor_gate(t1.xor_gate(ram[262], ram[263]), ram[260]);

      ram[260] = t1.or_gate(t1.and_gate(ram[262], ram[263]), t1.and_gate(t1.xor_gate(ram[262], ram[263]), ram[260]));

      ram[261] |= (ram[264] << i);
  }
  return ram[261];  
}

nano_math nm;
thread1 t1;
thread2 t2;
firmware fw;
