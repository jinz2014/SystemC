#include <systemc.h>
#include "tb.h"
int sc_main (int, char **) 
{
  unsigned size= 16;
 
  tb tb1("tb1", size);
  sc_trace_file *tf = sc_create_vcd_trace_file("fifo");
  sc_trace(tf,tb1.fifo1.clk,"clk");  
  sc_trace(tf,tb1.fifo1.rst,"rst");  
  sc_trace(tf,tb1.fifo1.full,"full");  
  sc_trace(tf,tb1.fifo1.empty,"empty");  
  sc_trace(tf,tb1.fifo1.write_enable,"wr_en");  
  sc_trace(tf,tb1.fifo1.write_data,"wdata");  
  sc_trace(tf,tb1.fifo1.read_data,"fifodin");  
  sc_trace(tf,tb1.fifo1.read_enable,"rd_en");  
  sc_trace(tf,tb1.fifo1.read_data,"rdata");  
  
  cout <<"Testbench started,the simulation result is:" << endl;
  sc_start(100000, SC_NS);  
  cout<<"\n"<<endl;
  sc_close_vcd_trace_file(tf);
  return 0;
}