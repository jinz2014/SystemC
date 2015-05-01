#ifndef _PORTLESS_H
#define _PORTLESS_H
#include "systemc.h"
#include "ram.h"
SC_MODULE(PortLess){
	sc_in_clk clk;	
	ram<int> *ram0;
	void main_action();
	SC_CTOR(PortLess){
		SC_CTHREAD(main_action,clk.pos());
		ram0=new ram<int>("RAM",0,255);
		
	}
};
#endif
void PortLess::main_action(){
	int data=0;	
	unsigned int address=ram0->start_address();
	unsigned int end_address=ram0->end_address();
	
	wait();
    while(address<=end_address){
		ram0->write(address,data);
		cout<<"RAM write at address:"<<address<<",data is:"<<data<<endl;
		wait();
        ram0->read(address,data);
		cout<<"RAM read at address:"<<address<<",data is:"<<data<<endl;
		address++;
		data+=2;
		wait();
	}
	sc_stop();
}