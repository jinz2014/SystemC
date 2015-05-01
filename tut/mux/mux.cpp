// A 4-1 8-bit MUX
// file: mux.cpp

#include "mux.h"

void mux::prc_mux() {
  sc_int<WORD> ta, tb, tc, td;
  sc_uint<SELECT> s;

  ta = a.read();
  tb = b.read();
  tc = b.read();
  td = b.read();
  s  = sel.read();

  switch(s) {
    case 0  : r = ta; break;
    case 1  : r = tb; break;
    case 2  : r = tc; break;
    case 3  : r = td; break;
  }
}


