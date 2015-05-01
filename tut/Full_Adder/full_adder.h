#include "systemc.h"
#include "my_half_adder.h"

SC_MODULE (full_adder) {
  sc_in<bool>  x, y, ci;
  sc_out<bool> s, co;

  sc_signal<bool> s1, c1, c2;

  // no args and return val
  void logic_or ();

  my_half_adder *ha1, *ha2;

  SC_CTOR (full_adder) {

    // inside constructor
    ha1 = new my_half_adder("ha1");
    ha1->x(x);
    ha1->y(y);
    ha1->s(s1);
    ha1->co(c1);

    ha2 = new my_half_adder("ha2");
    ha2->x(s1);
    ha2->y(ci);
    ha2->s(s);
    ha2->co(c2);

    SC_METHOD (logic_or);
    sensitive << c1;
    sensitive << c2;
  }

  // A destructor 
  ~full_adder() {
    delete ha1;
    delete ha2;
  }

};  // tricky semicolon





