#ifndef _MULTI_RAM_IF_H
#define _MULTI_RAM_IF_H
#include "systemc.h"
#include "multi_ram_if.h"

template <class T>
class mmu : public sc_module, public multi_ram_if<T> {
  public:
    sc_port<ram_if<int>, 0> ram_port;

    mmu (sc_module_name name) :
        sc_module (name) 
        {}

  transfer_status write (unsigned int address, T& data) {
    for (int i = 0; i < ram_port.size(); i++) {
      if (address >= ram_port[i]->start_address() && 
          address <= ram_port[i]->end_address()) {
        cout << "write ram " << i ;
        return ram_port[i]->write(address, data);
      }
    }
    return TRANSFER_ERR;
  }

  transfer_status read (unsigned int address, T& data) {
    for (int i = 0; i < ram_port.size(); i++) {
      if (address >= ram_port[i]->start_address() && 
          address <= ram_port[i]->end_address()) {
        cout << "read ram " << i ;
        return ram_port[i]->read(address, data);
      }
    }
    return TRANSFER_ERR;
  }

  bool reset() {
    for (int i = 0; i < ram_port.size(); i++)
      ram_port[i] -> reset();
  }

  bool reset(unsigned int i) {
    if (i < ram_port.size())
      return ram_port[i]->reset();
    else 
      return false;
  }

  inline unsigned int start_address() const {} 
  inline unsigned int end_address() const {}
};


#endif

