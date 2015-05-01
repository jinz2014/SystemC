// File: four_bit_adder.cpp
#include "four_bit_adder.h"
#include "one_bit_adder.h"

void four_bit_adder::prc_four_bit_adder () {
  sc_uint<SIZE + 1> tcarry;
  sc_uint<SIZE> tsum, tsha, tshb;
  int j;
  bool sum_bit, carry_bit;

  tsha = sha.read();
  tshb = shb.read();
  tcarry[0] = shcarry_in.read();

  for (j = 0; j < SIZE; j++) {
    one_bit_adder((bool)tsha[j], (bool)tshb[j], (bool)tcarry[j], sum_bit, carry_bit);
    tsum[j] = sum_bit;
    tcarry[j+1] = carry_bit;
  }

  shcarry_out = tcarry[SIZE];
  shsum = tsum;
}
 
