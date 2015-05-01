#ifndef _MULTI_MEM_IF_H
#define _MULTI_MEM_IF_H

#include "systemc.h"
#include "ram_if.h"

template<class T>
class multi_ram_if: public ram_if<T> {
  virtual bool reset(unsigned int i) = 0;
};


#endif
