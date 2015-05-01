#include "systemc.h"

SC_MODULE(driver) {
  sc_out<sc_lv<4> > d_pattern;

  void prc_driver();

  SC_CTOR(driver) {
    SC_THREAD(prc_driver);
  }
};

