#include "systemc.h"

SC_MODULE (detector) {
  sc_in<bool> clk, data;
  sc_out<bool> seq_detected;

  void prc_detect();

  void prc_output();

  sc_signal<bool> one, two, three;

  SC_CTOR(detector) {
    SC_METHOD(prc_detect) ;
    sensitive_pos << clk;   // edge sens

    SC_METHOD(prc_output);
    sensitive << one << two << three;   // event sens
  };
};
