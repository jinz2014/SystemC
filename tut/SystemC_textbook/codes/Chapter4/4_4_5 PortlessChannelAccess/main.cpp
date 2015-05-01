//sc_main 
#include "systemc.h"
#include "top.h"
int sc_main(int, char**){	
	sc_clock clk("clk",10,SC_NS);
	Top top1("top");	
	top1.clk(clk);
	sc_start(1000);
	return 0;
}