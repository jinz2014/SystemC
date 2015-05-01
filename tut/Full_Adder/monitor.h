#include "systemc.h"
SC_MODULE (tb_monitor) {
  sc_in<bool>  m_x, m_y, m_ci, m_s, m_co;

  void monitor();

  SC_CTOR (tb_monitor) {
    SC_METHOD (monitor);
    sensitive << m_x, m_y, m_ci, m_s, m_co;
  }
};


