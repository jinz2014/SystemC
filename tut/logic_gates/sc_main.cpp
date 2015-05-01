#include "logic_gate.h"
#include "driver.h"
#include "monitor.h"


int sc_main(int argc, char* argv[]) {

  sc_signal<sc_lv<4> > pattern;
  sc_signal<sc_logic> t_z;

  gate_type type;
  logic_gate *g1;

  // parameterized constructor
  type = AND;
  g1 = new logic_gate("gate1", type);

  g1->in(pattern);
  g1->z(t_z);

  driver d ("GenerateStimulus");
  d.d_pattern(pattern);

  monitor m1("monitor1");
  m1.m_pattern(pattern);
  m1.m_z(t_z);

  sc_trace_file *fp;
  fp = sc_create_vcd_trace_file("Wave");

  /*
  char *buf= new char[4];
  sc_lv<4> data;
  for (int i = 0; i < 4; i++) {
    sprintf(buf, "[%d]", i);
    data = pattern.read();
    sc_trace(fp, data[i], "Pattern"+buf);
  }
  */

  sc_trace(fp, pattern, "Pattern");
  sc_trace(fp, t_z, "Result");


  sc_start(1000, SC_NS);

  delete g1;

  sc_close_vcd_trace_file(fp);

  sc_start(-1);

  return 0;
}

