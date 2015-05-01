#ifndef __MAIN_TLM_H__
#define __MAIN_TLM_H__
#include <systemc.h>
#include "tb.h"
int sc_main (int, char **) 
{
  unsigned size= 16;
 
  tb tb1("tb1", size); 
   
  cout <<"Testbench started,the simulation result is:" << endl;
  sc_start(100000, SC_NS);  
  cout<<"\n"<<endl;
  
  return 0;
}
#endif