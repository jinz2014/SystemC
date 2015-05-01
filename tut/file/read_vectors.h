#include <iostream>
#include <fstream>
#include "systemc.h"
#include "user_define.h"

SC_MODULE (read_vectors) {
  sc_in<bool> read_clk;
  sc_out<sc_uint<SEL_WIDTH> > read_sel_op;
  sc_out<sc_uint<WIDTH> >     read_data1, read_data2;

  void prc_read_vectors();
  ifstream infile;

  SC_CTOR(read_vectors) {

    SC_METHOD(prc_read_vectors);
    sensitive_neg << read_clk;

    infile.open("usr.in");
    
    if (!infile) {
      cerr << "usr.in file not open" << endl;
      sc_stop();
    }
  }
};

