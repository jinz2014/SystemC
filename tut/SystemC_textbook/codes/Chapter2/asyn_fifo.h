//By Chenxi,2003.3.10
//-----------------
//asyn_fifo.h
//-----------------
#include "systemc.h"
#define DEPTH 1024
SC_MODULE(asyn_fifo) {
sc_in_clk           rd_clk,wr_clk;//clocks.they can be different in Fre.
sc_in<bool>         rst;          //high active reset,
sc_in<bool>         wr_en,rd_en;  //read enable and write enable
sc_in<int>          data_in;      //32bit in width
sc_out<bool>        full,empty;
sc_out<sc_uint<8> > data_count; 
sc_out<int>         data_out;
sc_signal<int>      ptr_wr,ptr_rd;//read pointer and write point 
int mem[DEPTH];                   // local memory storage
int i;
void write();
void read();
void exchange_pointer();
......
SC_CTOR(ram){
SC_METHOD(write);
sensitive << wr_clk<<rst;
SC_METHOD(read)
sensitive <<rd_clk<<rst;
SC_METHOD(synchronize_pointer);
sensitive<<wr_clk<<rd_clk<<rst<<ptr_wr<<ptr_rd;
for (i=0; i++; i<DEPTH) {mem[i] = 0;}
}
};
