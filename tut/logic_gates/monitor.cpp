#include <string>
#include "monitor.h"

void monitor::prc_monitor()
{
  // As with bit vectors, bit selection and range
  // selection cannot be performed on ports and
  // signals of logic vector type directly.
  sc_lv<4> var_pattern(m_pattern);

  cout /*<< "Gate " << get_type(m_type)*/ \
       << " at " << sc_simulation_time() \
       << " gate inputs are : "\
       <<var_pattern[3] << " , " \
       <<var_pattern[2] << " , " \
       <<var_pattern[1] << " , " \
       <<var_pattern[0] << " output is : "
       <<m_z<<endl;
}

/*
string monitor::get_type(gate_type type) {
  string op;
  switch (type) {
    case AND: op = "AND"; break;
    case NAND:op = "NAND"; break;
    case OR:  op = "OR"; break;
    case NOR: op = "NOR"; break;
    case XOR: op = "XOR"; break;
    default:  op = "N/A" ; break;
  }
  return op;
}
*/
  

