#ifndef __master_direct_h
#define __master_direct_h

#include <systemc.h>

#include "direct_if.h"


SC_MODULE(master_direct)
{
  // ports
  sc_in_clk clock;
  sc_port<direct_if> bus_port;

  SC_HAS_PROCESS(master_direct);

  // constructor
  master_direct(sc_module_name name_
                           , unsigned int address
                           , int timeout
                           , bool verbose = true)
    : sc_module(name_)
    , m_address(address)
    , m_timeout(timeout)
    , m_verbose(verbose)
  {
    // process declaration
    SC_THREAD(main_action);
  }

  // process
  void main_action();

private:
  unsigned int m_address;
  int m_timeout;
  bool m_verbose;

}; // end class master_direct

#endif
