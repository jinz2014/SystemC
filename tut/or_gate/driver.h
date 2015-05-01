#include "systemc.h"

SC_MODULE(driver)
{
  sc_out<sc_bit> d_a;
  sc_out<sc_bit> d_b; //inputs to the OR gate are of type sc_bit

  void drivea();
  void driveb();// these are two processes to stimulate the OR gate

  SC_CTOR(driver)
  {
    SC_THREAD (drivea);
    SC_THREAD (driveb);//processes are called here
  }
};
