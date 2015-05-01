#include "full_adder.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc, char *argv[]) {
  sc_signal<bool> t_x, t_y, t_ci, t_s, t_co;

  // no args and return val
  full_adder f1 ("1-bit_full_adder_instance");
  f1.x (t_x);
  f1.y (t_y);
  f1.ci(t_ci);
  f1.s (t_s);
  f1.co(t_co);

  tb_driver d1 ("Gen_wave");
  d1.d_x (t_x);
  d1.d_y (t_y);
  d1.d_ci(t_ci);

  tb_monitor m1 ("See_wave");
  m1.m_x (t_x);
  m1.m_y (t_y);
  m1.m_ci(t_ci);
  m1.m_s (t_s);
  m1.m_co(t_co);

  sc_start (100, SC_NS);

  // modelsim specific
  sc_start(-1);

  return (0);
}

