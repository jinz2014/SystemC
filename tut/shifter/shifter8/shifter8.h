// file: shifter8.h
#include "systemc.h"
#include "parameter.h"

SC_MODULE(shifter8) {
  sc_in<sc_bv<WORD> > din;
  sc_in<bool>         clk;
  sc_in<bool>         load;
  sc_in<bool>         LR;
  sc_inout<sc_bv<WORD> > dout;

  void prc_shifter() {

    // bit sel and range() can only be applied to var, not to ports or signals
    sc_bv<WORD> var_dout;

    var_dout = dout;

    if (load)
      var_dout = din;
    else if (LR) {
      var_dout.range(6,0) = var_dout.range(7,1);
      var_dout[7] = '0';
    } else {
      var_dout.range(7,1) = var_dout.range(6,0);
      var_dout[0] = '0';
    }

    dout = var_dout;
  }


  SC_CTOR(shifter8) {
    SC_METHOD(prc_shifter);
    sensitive_pos << clk;
  }
};

