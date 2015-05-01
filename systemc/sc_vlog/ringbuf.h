#ifndef _SCGENMOD_ringbuf_
#define _SCGENMOD_ringbuf_

#include "systemc.h"

class ringbuf : public sc_foreign_module
{
public:
    sc_in<bool> clock;
    sc_in<bool> reset;
    sc_in<bool> txda;
    sc_out<bool> rxda;
    sc_out<bool> txc;
    sc_out<bool> outstrobe;


    ringbuf(sc_module_name nm, const char* hdl_name,
       int num_generics, const char** generic_list)
     : sc_foreign_module(nm),
       clock("clock"),
       reset("reset"),
       txda("txda"),
       rxda("rxda"),
       txc("txc"),
       outstrobe("outstrobe")
    {
        elaborate_foreign_module(hdl_name, num_generics, generic_list);
    }
    ~ringbuf()
    {}

};

#endif

