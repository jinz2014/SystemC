#include "read_vectors.h"
#include "mux.h"
#include "user_define.h"

int sc_main(int argc, char *argv[]) {
  sc_signal<bool> read_clk;
  sc_signal<sc_uint<SEL_WIDTH> > sel_op;
  sc_signal<sc_uint<WIDTH> >     data1, data2; 
  sc_signal<sc_uint<WIDTH> >     out;

  sc_clock clk("clock", 10, SC_NS);

  read_vectors rv ("vector_file_read");
  rv.read_clk   (clk);
  rv.read_sel_op(sel_op);
  rv.read_data1 (data1);
  rv.read_data2 (data2);

  mux2 dut ("Mux2");
  dut.a (data1);
  dut.b (data2);
  dut.s (sel_op);
  dut.o (out);

  sc_start(100, SC_NS);

  sc_start(-1);

  return 0;
}
