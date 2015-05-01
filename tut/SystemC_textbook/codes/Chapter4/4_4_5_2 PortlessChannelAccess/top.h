//Top of the design
#include "systemc.h"
#include "ram.h"
#include "portless.h"
SC_MODULE(Top){
	sc_in_clk clk;
	PortLess* t1;
	SC_CTOR(Top){
	  t1=new PortLess("portless");
	  t1->clk(clk);
	}
	~Top(){
		if(t1) {delete t1;t1=0;}
	}
};
