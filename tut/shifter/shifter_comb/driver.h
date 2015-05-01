#include "systemc.h"
#include "parameter.h"

SC_MODULE(driver) {
  sc_out<sc_int<WORD> > d_data_in;
  sc_out<sc_uint<BITS> > d_num_bits;

  void prc_driver();

  SC_CTOR(driver) {
    SC_THREAD(prc_driver);
  }
};
