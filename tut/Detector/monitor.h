#include "systemc.h"
SC_MODULE (tb_monitor) {
  sc_in<bool>  m_data, m_detected;

  void monitor();

  SC_CTOR (tb_monitor) {
    SC_METHOD (monitor);
    sensitive << m_data, m_detected;
  }
};


