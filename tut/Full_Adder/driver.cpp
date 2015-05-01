#include "driver.h"

void tb_driver::driver () {
  sc_uint<3> pattern;
  pattern = 0;

  while (1) {
    d_x  = pattern [0];
    d_y  = pattern [1]; 
    d_ci = pattern [2];
    wait (5, SC_NS);
    pattern++;
  }
}
