#ifndef __master_non_blocking_h
#define __master_non_blocking_h

#include <systemc.h>

#include "types.h"
#include "non_blocking_if.h"


SC_MODULE(master_non_blocking)
{
  // ports
  sc_in_clk clock;
  sc_port<non_blocking_if> bus_port;

  SC_HAS_PROCESS(master_non_blocking);

  // constructor
  master_non_blocking(sc_module_name _name
				 , unsigned int unique_priority
                                 , unsigned int start_address
                                 , bool lock
                                 , int timeout)
    : sc_module(_name)
    , m_unique_priority(unique_priority)
    , m_start_address(start_address)
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
  unsigned int m_start_address;
  bool m_lock;
  int m_timeout;

}; // end class master_non_blocking

#endif
