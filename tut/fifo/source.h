#ifndef _SOURCE_H
#define _SOURCE_H
#include "systemc.h"
SC_MODULE (source) {
  sc_in_clk  clk;
  sc_port<sc_fifo_out_if<char> > write_port;

  SC_CTOR(source) {
    SC_THREAD(prc_source);
    sensitive_neg << clk;
  }

  void prc_source() {
    int i=0;
    const char str[] = "send a msg to fifo";
    wait();
    while (true) {
      if (rand() & 1) {
        if (str[i]) {
          cout << "free slots for write: " << write_port->num_free() << endl;
          write_port->write(str[i]);
          cout << " " << sc_time_stamp() << " send char " << str[i] << endl;
          i++;
        }
      }
      wait();
    }
  }
};
#endif
