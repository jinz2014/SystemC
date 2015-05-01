#ifndef _MAIN_H
#define _MAIN_H
#include "systemc.h"
#include "tb.h"

int sc_main (int, char **) {
  unsigned size = 16;

  tb tb("testbench", size);

  sc_start(1000, SC_NS);

  cout << "\n" << endl;

  cout << "simulation ends at " << sc_time_stamp();
  sc_start(-1);

  return 0;
}
#endif
