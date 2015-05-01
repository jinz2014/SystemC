#ifndef __TRISTATE_H
#define __TRISTATE_H
#include <systemc.h>
// Three-state buffer inference with resolved logic output
#include "systemc.h"
SC_MODULE(Tristate) {
  sc_in<bool> in_sela, in_selb;
  sc_in<bool> in_a; 
	sc_in<bool> in_b;
  sc_out_rv<1> out_1;
// Method for first three-state driver
  void tristate_a();
// Method for second three-state driver
  void tristate_b();
// Constructor
SC_CTOR( Tristate) {
  SC_METHOD( tristate_a);
  sensitive << in_sela << in_a;
  SC_METHOD( tristate_b);
  sensitive << in_selb << in_b;
}
};
void Tristate::tristate_a() {
  if (in_sela.read()){
out_1.write(in_a.read());
/*
	if(in_a.read()==SC_LOGIC_1) out_1.write("1");
    if(in_a.read()==SC_LOGIC_0) out_1.write("0");
	if(in_a.read()==SC_LOGIC_Z) out_1.write("Z");
    if(in_a.read()==SC_LOGIC_X) out_1.write("X");
*/
  }else{
    out_1.write("Z");//SC_LOGIC_Z
  }
}
void Tristate::tristate_b() {
  if (in_selb.read()){
out_1.write(in_b.read());
/*
	if(in_b.read()==SC_LOGIC_1) out_1.write("1");
    if(in_b.read()==SC_LOGIC_0) out_1.write("0");
	if(in_b.read()==SC_LOGIC_Z) out_1.write("Z");
    if(in_b.read()==SC_LOGIC_X) out_1.write("X");
	*/
}else{
out_1.write("Z");
}
}
#endif