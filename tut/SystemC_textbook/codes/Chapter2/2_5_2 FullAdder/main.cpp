//Chenxi
//
#include "systemc.h"
#include "FullAdder.h"
#include "Driver.h"
#include "Monitor.h"
int sc_main(int,char**){
	sc_clock clk("CLK",20,SC_NS);
    FullAdder *Adder;
	Driver *Dri; 
	Monitor *Mon;
 	sc_signal<sc_bit> a,b,ci,s,co;
	sc_signal<bool> rst,display_debug;
	rst.write(true);
	display_debug.write(true);
	Adder=new FullAdder("Adder"); 
	(*Adder)(a,b,ci,s,co);
	Dri= new Driver("Driver");
	(*Dri)(clk,rst,display_debug,a,b,ci);
	Mon =new Monitor("Monitor");
	(*Mon)(a,b,ci,s,co);	
	sc_start(100);
	rst.write(false);
    sc_start(200);
	return 0;
}