//Designed By Chenxi,2003.3.22
//a systemc description of 2-input nand gate
#ifndef _NAND2_H
#define _NAND2_H
#include <systemc.h>
#include <math.h>
SC_MODULE(nand2){
sc_in<bool> A;
sc_in<bool> B;
sc_out<bool> F;
void do_nand(){
F=!( A & B);
};
SC_CTOR(nand2){
SC_METHOD(do_nand);
sensitive<<A<<B;
}
};
#endif
