#include "systemc.h"
#include "monitor.h"

void tb_monitor::monitor () {
  cout << "At time "       << sc_time_stamp() << " ";
  cout << "input data: "   << m_data << " "; 
  cout << "101 detected: " << m_detected << endl;
}

