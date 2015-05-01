#ifndef _RESET_IF_H
#define _RESET_IF_H
#include <systemc.h>
class reset_if:public sc_interface{
public:
	virtual void reset(unsigned int interval)=0;
};

#endif