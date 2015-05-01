#include "systemc.h"

int sc_main(int argc, char *argv[]) {

  // signals decl
  sc_signal<int> sig;

  // clock setup
  sc_clock clk("clock", 10, SC_NS);

  // blocks connected to channel(s) and clock(s)
  writer w("writer");
  reader r("reader");

  w.clk(clk);
  w.out(sig);
  r.in(sig);

  // simulation start and stop
  sc_start (100, SC_NS);

  // modelsim specific
  sc_start(-1);

  return (0);
}

