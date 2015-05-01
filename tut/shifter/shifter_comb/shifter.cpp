// file: shifter.cpp
#include "shifter.h"

void shifter::prc_shifter() {
  sc_int<WORD> din;
  sc_uint<BITS> shamt;

  din   = data_in.read();
  shamt = num_bits.read();

  data_out = din >> shamt;
}


