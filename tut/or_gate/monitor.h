//file: monitor.h
//this the monitor module
#include "systemc.h"

SC_MODULE(monitor)
{
  //both input and output of the OR module are to be monitored
  sc_in<sc_bit> m_a, m_b;
  sc_in<sc_bit> m_c;

  void prc_monitor()
  {
    cout <<" At "<<sc_simulation_time()<<" input is : ";
    cout <<m_a<<" , "<<m_b<<" output is : "<<m_c<<endl;
  }

  SC_CTOR(monitor)
  {

    SC_METHOD(prc_monitor);
    sensitive << m_a <<m_b <<m_c;
    //whenever the i/p to the gate changes, 
    //or the o/p changes, the process prc_monitor triggers
  }
};
