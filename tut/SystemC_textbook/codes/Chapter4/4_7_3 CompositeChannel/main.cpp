#include "tb.h"
#include <systemc.h>
int sc_main (int, char **) 
{
  unsigned size= 16;
 
  tb tb1("tb1", size);
  sc_start(100000, SC_NS);  
  cout<<"\n"<<endl;
  return 0;
}