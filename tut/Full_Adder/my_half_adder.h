// definition of half adder 
// declaration of add process
#include "systemc.h"
SC_MODULE (my_half_adder) {
  sc_in<bool>  x, y;
  sc_out<bool> s, co;

  // no args and return val
  void add ();

  SC_CTOR (my_half_adder) {
    SC_METHOD (add);
    sensitive << x;
    sensitive << y;
  }
};  // tricky semicolon


