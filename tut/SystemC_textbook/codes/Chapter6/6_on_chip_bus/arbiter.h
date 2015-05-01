
#ifndef __arbiter_h
#define __arbiter_h

#include <systemc.h>

#include "types.h"
#include "request.h"
#include "arbiter_if.h"
//
class arbiter
  : public arbiter_if
  , public sc_module
{
public:
  // constructor
  arbiter(sc_module_name name_
                     , bool verbose = false)
    : sc_module(name_)
    , m_verbose(verbose)
  {}

  request *arbitrate(const request_vec &requests);

private:
  bool m_verbose;

}; // end class arbiter

#endif
