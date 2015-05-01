#include "parameter.h"
#include "driver.h"

void driver::prc_driver() {
  sc_uint<WORD> pattern;
  pattern = 0;

  while(1) {
    // int -> uint
    d_data_in = (sc_int<WORD>)pattern;
    d_num_bits = pattern.range(2,0);
    wait(5, SC_NS);
    pattern++;
  }
}
