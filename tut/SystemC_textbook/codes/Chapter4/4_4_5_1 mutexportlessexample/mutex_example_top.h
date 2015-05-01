#include "systemc.h"
#include "mutex_example.h"

SC_MODULE(mutex_example_top){

   mutex_example *me1;
   sc_in_clk clk;
   sc_signal<int> data_out;

   SC_CTOR(mutex_example_top){
     me1 =new mutex_example("mutex_example"); 
     me1->clk(clk);
     me1->data(data_out);
   }

  ~mutex_example_top(){
    if(me1) {delete me1;me1=0;}
  }
};
