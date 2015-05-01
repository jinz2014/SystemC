#include "systemc.h"

template<int width>
  SC_MODULE (tristate) {
    sc_in<sc_uint<width> > in_bus;
    sc_in<bool> oen;
    sc_out<sc_lv<width> > out_bus;

    void prc_tristate() {
      // init
      sc_lv<width> all_zs (sc_logic_Z);

      if (oen)
        out_bus = in_bus.read();
      else
        out_bus = all_zs;
    }

    SC_CTOR (tristate) {
      SC_METHOD (prc_tristate);
      sensitive << in_bus << oen;
    }
  };

template<int width>
  SC_MODULE (reg) {
    sc_in<sc_uint<width> > d;
    sc_in<bool> en, clk, rst;
    sc_out<sc_uint<width> > q;

    void prc_reg() {
      if (reset)
        q = 0;
      else if (en)
        q = d;
    }

    SC_CTOR (reg) {
      SC_METHOD (prc_reg);
      sensitive_pos << clk;
    }
  };

  const int SIZE = 32;
  SC_MODULE (tristate_reg) {
    sc_in<bool> clk, rst, reg_en, oen;
    sc_in<sc_uint<width> > din;
    sc_out<sc_lv<width> > dout;

    reg<SIZE> *inst1;
    tristate<SIZE> *inst2;

    sc_signal<sc_uint<SIZE> > reg_out;

    SC_CTOR (tristate_reg) {
      inst1 = new reg<SIZE> ("register");
      inst1->clk(clk);
      inst1->rst(rst);
      inst1->d(din);
      inst1->en(reg_en);
      inst1->q(reg_out);

      inst2 = new tristate<SIZE> ("tristate");
      inst2->in_bus(reg_out);
      inst2->oen(oen);
      inst2->out_bus(dout);
    }
  };

