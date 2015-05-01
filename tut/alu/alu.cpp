// file: alu.cpp
#include "alu.h"

void alu::prc_alu() {
  sc_int<WORD> ta, tb;

  ta = a.read();
  tb = b.read();
  z = 0;
  r = 0;
  
  switch(op) {
    case add  : r = ta + tb; break;
    case sub  : r = ta - tb; break;
    case mul  : r = ta * tb; break;
    case div  : r = ta / tb; break;
    case nand : r = ~(ta & tb); break;
    case xor  : r = ta ^ tb; break;
    case gt   : z = (ta > tb) ? 1 : 0; break;
    case eq   : z = (ta == tb) ? 1 : 0; break;
    //default   : ; break;
  }
}


