#ifndef _GET_FIFO_IF_H
#define _GET_FIFO_IF_H
#include <systemc.h>

class getFIFO_if:virtual public sc_interface{
public:
	virtual sc_fifo_in_if<char> getReadFIFO()=0;
    virtual sc_fifo_out_if<char> getWriteFIFO()=0;
    
};
#endif