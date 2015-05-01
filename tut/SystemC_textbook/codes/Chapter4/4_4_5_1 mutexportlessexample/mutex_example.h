#ifndef _MUTEX_EXAMPLE_H
#define _MUTEX_EXAMPLE_H
#include "systemc.h"
SC_MODULE(mutex_example){
	sc_in_clk clk;
	sc_out<int> data;
	sc_mutex protect;

	void writer1(){		
		wait();
		while(true){
			protect.lock();
      data=rand();
			cout<< sc_time_stamp() << " data is written by writer1, data is "<<data<<endl;
		  protect.unlock();
		  wait();
    } 
	}

  void writer2(){
	wait();
	while(true){
			protect.lock();
            data=rand();
			cout<< sc_time_stamp() << " data is written by writer2, data is "<<data<<endl;
		    protect.unlock();
			wait();}
	}

	void reader(){ 		
	    cout<< sc_time_stamp() << " reader detects that data changed to "<<data<<endl;		
	}

	SC_CTOR(mutex_example){
    SC_METHOD(reader);		 
    sensitive<<data;

    SC_CTHREAD(writer1,clk.pos());
    SC_CTHREAD(writer2,clk.pos());
	}
};
#endif
