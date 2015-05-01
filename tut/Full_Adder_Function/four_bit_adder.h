// File four_bit_adder.h
#include "systemc.h"
const int SIZE = 4;

SC_MODULE (four_bit_adder) {
  sc_in<sc_uint<SIZE> > sha, shb;
  sc_in<bool> > shcarry_in;
  sc_out<sc_uint<SIZE> > shsum;
  sc_out<bool> > shcarry_out;

  void proc_four_bit_adder ();

  SC_CTOR (four_bit_adder) {
    SC_METHOD(prc_four_bit_adder);
    sensitive << sha << shb << shcarry_in;
  }
};

