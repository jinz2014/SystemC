#include <systemc.h>
SC_MODULE(test){
	sc_in_clk clk;
	sc_out<bool> rst,detect;
	sc_in<bool> syn_ind;
	void assign_value(){
		rst.write(true);
		while(true){
			rst.write(false);
			detect.write(true);
			wait();wait();wait();
		}
	}
	SC_CTOR(test){
        SC_CTHREAD(assign_value,clk.pos());
	}
};