
#ifndef _MEM_IF_H
#define _MEM_IF_H
#include "systemc.h"

enum transfer_status { TRANSFER_OK = 0, TRANSFER_ERR }; 

template <class T>

class ram_if: public sc_interface {
  public:
    virtual transfer_status read (unsigned int address, T& data) = 0;
    virtual transfer_status write (unsigned int address, T& data) = 0;
    virtual bool reset() = 0;
    virtual unsigned int start_address() const = 0;
    virtual unsigned int end_address() const = 0;
};

/* ===========  ambiguous base class ======================= 
// template class : byte, word, doubleword or even a packet access
template <class T>
class mem_read_if: public sc_interface {
  public:
    virtual transfer_status read (unsigned int address, T& data) = 0;
};

template <class T>
class mem_write_if: public sc_interface {
  public:
    virtual transfer_status write (unsigned int address, T& data) = 0;
};

class reset_if: public sc_interface {
  public:
    virtual bool reset() = 0;
};



template <class T>
class ram_if: public mem_write_if<T>, public mem_read_if<T>, public reset_if {
  public:
    virtual unsigned int start_address() const = 0;
    virtual unsigned int end_address() const = 0;
};
*/

#endif
