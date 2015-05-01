#include "systemc.h"
#include "user_define.h"

SC_MODULE (mux2) {
  //sc_in<bool> a1, a2, a3, a4; // input ports of the multiplexer
  sc_in<sc_uint<WIDTH> >      a, b;
  sc_in<sc_uint<SEL_WIDTH> >  s;
  sc_out<sc_uint<WIDTH> >     o; // output port

  void mux (); // Process

  SC_CTOR (mux2)
  {
    SC_METHOD (mux);
    sensitive << s << a << b; 
  }
};
