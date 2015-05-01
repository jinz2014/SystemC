#include "systemc.h"
SC_MODULE (reader)
{
  sc_in<int> in;

  void main_action()
  {
    int val;
    while (true) {
      wait();    // wait for pos clk
      val = in;
      cout << val << endl;
    }
  }

  SC_CTOR (reader) 
  {
    SC_THREAD (main_action);
    sensitive << in;
  }
}

