#include "monitor.h"

void monitor::prc_monitor () {
  cout << "At time " << sc_time_stamp() << "::";
  cout << "(data_in, num_bits): ";
  cout << m_data_in << " " << m_num_bits;
  cout << "(data_out) : " << m_data_out << endl;
}

