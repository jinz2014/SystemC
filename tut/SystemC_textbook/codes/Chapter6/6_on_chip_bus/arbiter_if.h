#ifndef __arbiter_if_h
#define __arbiter_if_h

#include <systemc.h>

#include "types.h"


class arbiter_if
  : public virtual sc_interface
{
public:
  virtual request * 
    arbitrate(const request_vec &requests) = 0;

}; // end class arbiter_if

#endif
