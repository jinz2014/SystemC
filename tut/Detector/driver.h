#include "systemc.h"
SC_MODULE (tb_driver) {
  sc_in<bool>   clk;
  sc_out<bool>  data;

  void driver();

  SC_CTOR (tb_driver) {
    SC_CTHREAD (driver, clk.neg());
  }
};

