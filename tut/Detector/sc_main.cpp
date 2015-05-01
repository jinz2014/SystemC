#include "detector.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc, char *argv[]) {

  // signals decl
  sc_signal<bool> data, detected;

  // clock setup
  sc_clock clk("clock", 10, SC_NS);

  // module instantiations
  detector u1 ("simple_101_detector");
  u1.clk         (clk);
  u1.data        (data);
  u1.seq_detected(detected);

  tb_driver d1 ("Gen_wave");
  d1.clk  (clk);
  d1.data (data);

  tb_monitor m1 ("See_wave");
  m1.m_data    (data);
  m1.m_detected(detected);

  // traces files

  // simulation start and stop
  sc_start (1000, SC_NS);

  // modelsim specific
  sc_start(-1);

  return (0);
}

