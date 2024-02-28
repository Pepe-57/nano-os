#ifndef FIRMWARE_H
#define FIRMWARE_H

void init_all();
class thread1 {
public:
  //Main function
  int nand(int a0, int b0);
  //Logic Gates
  int not_gate(int a0);
  int or_gate(int a0, int b0);
  int nor_gate(int a0, int b0);
  int and_gate(int a0, int b0);
  int xor_gate(int a0, int b0);
  int sto_reg(int a, int b);
  int sto(int a, int b);
};

class thread2 {
public:
  //Main function
  int nand(int a1, int b1);
  int not_gate(int a1);
  int or_gate(int a1, int b1);
  int nor_gate(int a1, int b1);
  int and_gate(int a1, int b1);
  int xor_gate(int a1, int b1);
  int sto_reg(int a, int b);
  int sto(int a, int b);
};

extern thread1 t1;
extern thread2 t2;
extern int ram[512];

#endif
