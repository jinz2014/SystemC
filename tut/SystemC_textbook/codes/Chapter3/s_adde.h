/****s_adde.h м╥нд╪Ч****/
#include "systemc.h"
SC_MODULE(s_adder_c) {
	sc_in<sc_int<4> > a, b;
	sc_out <sc_int<4> > sum;
	sc_out <bool> carry_out;	
	void prc_s_adder_c();	
	SC_CTOR(s_adder_c) {
		SC_METHOD(prc_s_adder_c);
		sensitive << a << b;
	}
};
