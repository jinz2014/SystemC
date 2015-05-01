//By Chenxi
#ifndef __slave_if_h
#define __slave_if_h
#include <systemc.h>
#include "types.h"
#include "direct_if.h"

class slave_if
  : public direct_if
{
public:
  // Slave interface
  virtual status read(int *data, unsigned int address) = 0;
  virtual status write(int *data, unsigned int address) = 0;

  virtual unsigned int start_address() const = 0;
  virtual unsigned int end_address() const = 0;

}; // end class slave_if

#endif
