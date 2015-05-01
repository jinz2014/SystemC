#include "driver.h"

void driver::prc_driver() {
  sc_uint<4> var_pattern;
  var_pattern = 0;

  while(1) {
    d_pattern = var_pattern;
    wait(5, SC_NS);
    var_pattern++;
  }
}

