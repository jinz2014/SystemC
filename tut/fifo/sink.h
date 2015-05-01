#ifndef _SINK_H
#define _SINK_H
#include "systemc.h"
SC_MODULE (sink) {
  sc_in_clk  clk;
  sc_port<sc_fifo_in_if<char> > read_port;

  SC_CTOR(sink) {
    SC_THREAD(prc_sink);
    sensitive_neg << clk;
  }

  void prc_sink() {
    char c;
    wait();
    while (true) {
      if (rand() & 1) {
        cout << "available slots for read: " << read_port->num_available() << endl;
        read_port->read(c);
        cout << " " << sc_time_stamp() << " recv char " << c << endl;
      }
      wait();
    }
  }
};


#endif
