// A 4-1 8-bit MUX
// file: mux.h

#include "systemc.h"
const int WORD = 8;
const int SELECT = 2;

SC_MODULE(mux) {
  sc_in<sc_int<WORD> > a, b, c, d;
  sc_in<sc_uint<SELECT> > sel;
  sc_out<sc_int<WORD> > r;

  void prc_mux();

  SC_CTOR(mux) {
    SC_METHOD(prc_mux);
    //sensitive << a << b << op;
    sensitive (a, b, c, d, sel);
  }
};
