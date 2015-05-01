/****xor_gates.h м╥нд╪Ч****/
#include "systemc.h"
SC_MODULE(xor_gates) {
sc_in<sc_uint<4> > bre, sty;
sc_out <sc_uint<4> > tap;
void prc_xor_gates();
SC_CTOR(xor_gates) {
		   SC_METHOD(prc_xor_gates);
		   sensitive << bre << sty;
}
}
