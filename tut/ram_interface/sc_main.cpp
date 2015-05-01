#include "top.h"
#include "systemc.h"

int sc_main(int argc, char *argv[]) {

  // signals decl

  // clock setup
  sc_clock clk("clock", 10, SC_NS);

  top tb ("testbench");
  tb.clk(clk);

  // traces files

  // simulation start and stop
  sc_start (1000, SC_NS);

  // modelsim specific
  sc_start(-1);

  return (0);
}

