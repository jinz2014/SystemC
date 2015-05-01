//file: monitor.h
//this the monitor module
#include <string>
#include "systemc.h"
#include "type.h"

SC_MODULE(monitor)
{
  sc_in<sc_lv<4> > m_pattern;
  sc_in<sc_logic> m_z;
  //sc_in<gate_type> m_type;

  void prc_monitor();
  //string get_type(gate_type);

  SC_CTOR(monitor)
  {

    SC_METHOD(prc_monitor);
    sensitive << m_pattern <<m_z;
    //whenever the i/p to the gate changes, 
    //or the o/p changes, the process prc_monitor triggers
  }
};

