// File driver.h
//By Chenxi
#ifndef _DRIVER_H
#define _DRIVER_H

#include "systemc.h"
SC_MODULE(Driver) {	
	sc_in_clk clk;
	sc_in<bool> rst;
	sc_in<bool> display_debug;
	sc_out<sc_bit> d_a,d_b,d_cin;
	void prc_driver();
	SC_CTOR(Driver) {
		SC_CTHREAD(prc_driver,clk.pos());
		watching(rst.delayed()==true);
	}
};
#endif