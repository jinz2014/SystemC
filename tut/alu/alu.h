// file: alu.h
#include "systemc.h"
const int WORD = 2;
enum op_type {add, sub, mul, div, nand, xor, gt, eq}; 

SC_MODULE(alu) {
  sc_in<sc_int<WORD> > a, b;
  sc_in<sc_uint<op_type> > op;
  sc_out<sc_int<WORD> > r;
  sc_out<bool> z;

  void prc_alu();

  SC_CTOR(alu) {
    SC_METHOD(prc_alu);
    sensitive << a << b << op;
  }
};
