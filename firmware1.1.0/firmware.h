#ifndef FIRMWARE_H
#define FIRMWARE_H

class firmware {
public:
  void init_all();
  void init_core1();
  void init_core2();
  void start();
  int dce();
  int get_cpu_count();
  int get_ram_size();
  int get_registers();
};
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
  //Other functions
  int sto_reg(int addr, int reg);
  int sto(int addr, int data);
  int diec(int instruction);
};

class thread2 {
public:
  //Main function
  int nand(int a1, int b1);
  //Logic Gates
  int not_gate(int a1);
  int or_gate(int a1, int b1);
  int nor_gate(int a1, int b1);
  int and_gate(int a1, int b1);
  int xor_gate(int a1, int b1);
  //Other functions
  int sto_reg(int addr, int reg);
  int sto(int addr, int data);
  int diec(int instruction);
};

extern thread1 t1;
extern thread2 t2;
extern firmware fw;
extern int ram[];

#endif
