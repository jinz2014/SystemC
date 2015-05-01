#include "systemc.h"
#include "monitor.h"

void tb_monitor::monitor () {
  cout << "At time" << sc_time_stamp() << " ";
  cout << "(x,y,carray_in): ";
  cout << m_x << m_y << m_ci;
  cout << "(sum,carray_out): ";
  cout << m_s << m_co << endl;
}

