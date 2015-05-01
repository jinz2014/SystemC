#include "systemc.h"
#include "parameter.h"

SC_MODULE(monitor) {
  sc_in<sc_int<WORD> > m_data_in;
  sc_in<sc_uint<BITS> > m_num_bits;
  sc_in<sc_int<WORD> > m_data_out;

  void prc_monitor();

  SC_CTOR(monitor) {
    SC_METHOD(prc_monitor);
    sensitive << m_data_in << m_num_bits << m_data_out;
  }
};

