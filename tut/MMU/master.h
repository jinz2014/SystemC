#include "systemc.h"
#include "multi_ram_if.h"

SC_MODULE (Master) {
  sc_in_clk clk;
  sc_port<multi_ram_if<int> > multi_ram_port; // port instance

  int data;
  unsigned int address;
  void main_action();

  SC_CTOR(Master) {
    SC_CTHREAD (main_action, clk.pos());
  }
};

