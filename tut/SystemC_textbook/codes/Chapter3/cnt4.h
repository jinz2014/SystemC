/*cnt4.h м╥нд╪Ч*/
#include "systemc.h"
const int CSIZE = 4;
SC_MODULE(cnt4) {
	sc_in<bool> mclk, clear, updown;
	sc_out<sc_uint<CSIZE> > dout;
	void do_cnt4();
	SC_CTOR(cnt4) {
		SC_METHOD(do_cnt4);
		sensitive_pos << mclk;
		sensitive_neg << clear;
	  }
};

