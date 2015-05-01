#ifndef __master_blocking_h
#define __master_blocking_h

#include <systemc.h>

#include "types.h"
#include "blocking_if.h"


SC_MODULE(master_blocking)
{
  // ports
  sc_in_clk clock;
  sc_port<blocking_if> bus_port;

  SC_HAS_PROCESS(master_blocking);

  // constructor
  master_blocking(sc_module_name name_
			     , unsigned int unique_priority
			     , unsigned int address
                             , bool lock
                             , int timeout)
    : sc_module(name_)
    , m_unique_priority(unique_priority)
    , m_address(address)
    , m_lock(lock)
    , m_timeout(timeout)
  {
    // process declaration
    SC_THREAD(main_action);
    sensitive_pos << clock;
  }
  
  // process
  void main_action();

private:
  unsigned int m_unique_priority;
  unsigned int m_address;
  bool m_lock;
  int m_timeout;

}; // end class master_blocking

#endif
