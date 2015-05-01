//sc_main 
#include "systemc.h"
#include "mutex_example_top.h"
int sc_main(int, char**){	
	sc_clock clk("clk",10,SC_NS);
	mutex_example_top top("top");	
	top.clk(clk);
	sc_start(1000);
	return 0;
}