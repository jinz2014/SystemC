//By Chenxi
//blocking_if.h
#ifndef __blocking_if_h
#define __blocking_if_h
#include <systemc.h>
#include "types.h"
class blocking_if
  : public virtual sc_interface
{
public:
  // blocking BUS interface
  virtual status burst_read(unsigned int unique_priority
				       , int *data
				       , unsigned int start_address
				       , unsigned int length = 1
				       , bool lock = false) = 0;
  virtual status burst_write(unsigned int unique_priority
					, int *data
					, unsigned int start_address
					, unsigned int length = 1
					, bool lock = false) = 0;

}; // end class blocking_if
#endif
