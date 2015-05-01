#include "systemc.h"
const int WORD_SIZE = 8;
const int ADDR_SIZE = 6;
const int MEM_SIZE = 100;

SC_MODULE (memory) {
  sc_in<bool> en, rw, clk;
  sc_in<sc_uint<ADDR_SIZE> > addr;
  sc_inout<sc_lv<WORD_SIZE> > data;

  void prc_memory();

  sc_lv<WORD_SIZE> ram [MEM_SIZE];

  SC_CTOR (memory) {
    SC_METHOD (prc_memory);
    sensitive_neg << clk;
  }
};
