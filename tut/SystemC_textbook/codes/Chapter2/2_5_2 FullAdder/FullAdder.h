//Full Adder logic,By Chenxi,2003.5.25
#ifndef __FULLADDER_H
#define __FULLADDER_H
#include "systemc.h"
#include "fx.h"
SC_MODULE(FullAdder)
{
sc_in<sc_bit> A,B,Ci;
sc_out<sc_bit> S,Co;
void do_add()
{
 S=(A.read())^(B.read())^(Ci.read());
 Co=(A.read())&(B.read())|(B.read())&(Ci.read())|(A.read())&(Ci.read());
};
SC_CTOR(FullAdder)
{
SC_METHOD(do_add);
sensitive<<A<<B<<Ci;
}
};
#endif
