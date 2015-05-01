// file: shifter.h
#include "systemc.h"
#include "parameter.h"

SC_MODULE(shifter) {
  sc_in<sc_int<WORD> > data_in;
  sc_in<sc_uint<BITS> > num_bits;
  sc_out<sc_int<WORD> > data_out;

  void prc_shifter();

  SC_CTOR(shifter) {
    SC_METHOD(prc_shifter);
    sensitive << data_in << num_bits;
  }
};
