#include <systemc.h>
#include "fsm.h"
#include "test.h"
int sc_main(int, char**){
	sc_clock clk("clk");
	sc_signal<bool> rst,detect,syn_ind;
	fsm<3,5> fsm1("SYNCHRONIZER");
	fsm1.clk(clk);
	fsm1.rst(rst);
	fsm1.detect(detect);
	fsm1.syn_ind(syn_ind);
	test t("test");
    t.clk(clk);
	t.rst(rst);
	t.detect(detect);
	t.syn_ind(syn_ind);
	sc_start(1000);
	return 0;
}