#include "systemc.h"
SC_MODULE (tb_driver) {
  sc_out<bool>  d_x, d_y, d_ci;

  void driver();

  SC_CTOR (tb_driver) {
    SC_THREAD (driver);
  }
};

