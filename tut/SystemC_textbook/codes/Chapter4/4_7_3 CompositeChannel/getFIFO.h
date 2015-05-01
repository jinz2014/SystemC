#ifndef _GET_FIFO_H
#define _GET_FIFO_H
#include <systemc.h>
#include "getFIFO_if.h"
#include "fifo_hl.h"
class getFIFO:public getFIFO_if,public sc_module{
public:
    sc_in_clk clk; 	
    fifo_hl<char> *FIFO1;    
	getFIFO(sc_module_name name_, unsigned int size){
    FIFO1=new fifo_hl<char>(name_,size);
	FIFO1->clk(clk);
   }
    sc_fifo_in_if<char> getReadFIFO(){	return FIFO1;}
    sc_fifo_out_if<char> getWriteFIFO(){return *FIFO1;}    
	~getFIFO(){
		if(FIFO1) {delete FIFO1;FIFO1=0;}
	}	
    
};
#endif