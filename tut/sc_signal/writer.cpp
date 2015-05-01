#include "systemc.h"
SC_MODULE (writer)
{
  sc_out<int> out;
  sc_in_clk   clk;

  void main_action()
  {
    int val = 0;
    while (true) {
      wait();    // wait for pos clk
      out = val++;
    }
  }

  SC_CTOR (writer) 
  {
    SC_THREAD (main_action);
    sensitive_pos << clk;
  }
}

