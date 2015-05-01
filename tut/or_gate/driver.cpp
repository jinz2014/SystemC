#include "driver.h"

void driver :: drivea()
{
  d_a.write((sc_bit)false);//(ba)=00
  wait(5,SC_NS);
  d_a.write((sc_bit)true);//(ba)=01
  wait(5, SC_NS);
  d_a.write((sc_bit)0);//(ba)=10, false=0
  wait(5,SC_NS);
  d_a.write((sc_bit)1);//(ba)=11, true=1
  wait(5,SC_NS);
}

void driver :: driveb()
{
  d_b.write((sc_bit)0);
  wait(10,SC_NS);
  d_b.write((sc_bit)1);
  wait(5,SC_NS);
}
