#include "logic_gate.h"

void logic_gate::prc_and_gate() {
  sc_lv<4> data;
  data = in.read();
  z = data[3] & data[2] & data[1] & data[0];
}

void logic_gate::prc_nand_gate() {
  sc_lv<4> data;
  data = in.read();
  z = ~(data[3] & data[2] & data[1] & data[0]);
}
void logic_gate::prc_or_gate() {
  sc_lv<4> data;
  data = in.read();
  z = (data[3] | data[2] | data[1] | data[0]);
}
void logic_gate::prc_nor_gate() {
  sc_lv<4> data;
  data = in.read();
  z = ~(data[3] | data[2] | data[1] | data[0]);
}
void logic_gate::prc_xor_gate() {
  sc_lv<4> data;
  data = in.read();
  z = (data[3] ^ data[2] ^ data[1] ^ data[0]);
}

