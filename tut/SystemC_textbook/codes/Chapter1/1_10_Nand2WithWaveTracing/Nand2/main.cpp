//By chenxi,all rights reserved
//main.h
#include <systemc.h>
#include "nand2.h"
#include "tb.h"
int sc_main(int, char**){
	sc_signal<bool> a,b,f;
	sc_clock clk("Clk",20,SC_NS);
	nand2 N2("Nand2");
    N2.A(a);
    N2.B(b);
    N2.F(f);
    tb tb1("tb");
	tb1.clk(clk);
	tb1.a(a);
    tb1.b(b);
	tb1.f(f);	
	sc_start(200);
	return 0;
}