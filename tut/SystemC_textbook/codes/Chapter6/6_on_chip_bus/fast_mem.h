//By Chenxi
#ifndef __fast_mem_h
#define __fast_mem_h
#include <systemc.h>
#include "types.h"
#include "slave_if.h"
class fast_mem
  : public slave_if
  , public sc_module
{
public:
  // constructor
  fast_mem(sc_module_name name_
		      , unsigned int start_address
		      , unsigned int end_address)
    : sc_module(name_)
    , m_start_address(start_address)
    , m_end_address(end_address)
  {
    sc_assert(m_start_address <= m_end_address);
    sc_assert((m_end_address-m_start_address+1)%4 == 0);
    unsigned int size = (m_end_address-m_start_address+1)/4;
    MEM = new int [size];
    for (unsigned int i = 0; i < size; ++i)
      MEM[i] = 0;
	
  }

  // destructor
  ~fast_mem();
  // direct Slave Interface
  bool direct_read(int *data, unsigned int address);
  bool direct_write(int *data, unsigned int address);
  // Slave Interface
  status read(int *data, unsigned int address);
  status write(int *data, unsigned int address);
  unsigned int start_address() const;
  unsigned int end_address() const;

private:
  int * MEM;
  unsigned int m_start_address;
  unsigned int m_end_address;

}; // end class fast_mem

inline bool fast_mem::direct_read(int *data, unsigned int address)
{  return (read(data, address) == TRANSFER_OK);}

inline bool fast_mem::direct_write(int *data, unsigned int address)
{  return (write(data, address) == TRANSFER_OK);}

inline status fast_mem::read(int *data
						   , unsigned int address)
{
	if( address<m_start_address || address>m_end_address){
		*data =0;
        return TRANSFER_OK;
	}
  *data = MEM[(address - m_start_address)/4];
  return TRANSFER_OK;
}

inline status fast_mem::write(int *data
						    , unsigned int address)
{
  if( address<m_start_address || address>m_end_address)     
  return TRANSFER_ERROR; 
  MEM[(address - m_start_address)/4] = *data;  
  return TRANSFER_OK;
}

inline  fast_mem::~fast_mem()
{  if (MEM) delete [] MEM;  MEM = (int *)0;}

inline unsigned int fast_mem::start_address() const
{  return m_start_address;}

inline unsigned int fast_mem::end_address() const
{  return m_end_address;}
#endif
