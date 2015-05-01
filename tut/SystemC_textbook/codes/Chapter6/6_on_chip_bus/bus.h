#ifndef __h
#define __h

#include <systemc.h>

#include "types.h"
#include "request.h"
#include "direct_if.h"
#include "non_blocking_if.h"
#include "blocking_if.h"
#include "arbiter_if.h"
#include "slave_if.h"


class bus
  : public direct_if
  , public non_blocking_if
  , public blocking_if
  , public sc_module
{
public:
  // ports
  sc_in_clk clock;
  sc_port<arbiter_if> arbiter_port;
  sc_port<slave_if, 0> slave_port;

  SC_HAS_PROCESS(bus);

  // constructor
  bus(sc_module_name name_
             , bool verbose = false)
    : sc_module(name_)
    , m_verbose(verbose)
    , m_current_request(0)
  {
    // process declaration
    SC_METHOD(main_action);
    dont_initialize();
    sensitive_neg << clock;
  }

  // process
  void main_action();

  // direct BUS interface
  bool direct_read(int *data, unsigned int address);
  bool direct_write(int *data, unsigned int address);

  // non-blocking BUS interface
  void read(unsigned int unique_priority
	    , int *data
	    , unsigned int address
	    , bool lock = false);
  void write(unsigned int unique_priority
	     , int *data
	     , unsigned int address
	     , bool lock = false);
  status get_status(unsigned int unique_priority);

  // blocking BUS interface
  status burst_read(unsigned int unique_priority
			       , int *data
			       , unsigned int start_address
			       , unsigned int length = 1
			       , bool lock = false);
  status burst_write(unsigned int unique_priority
				, int *data
				, unsigned int start_address
				, unsigned int length = 1
				, bool lock = false);

private:
  void handle_request();
  void end_of_elaboration();
  slave_if * get_slave(unsigned int address);
  request * get_request(unsigned int priority);
  request * get_next_request();
  void clear_locks();

private:
  bool m_verbose;
  request_vec m_requests;
  request *m_current_request;

}; // end class simple_bus

#endif
