//By ChenXi
#ifndef __slow_mem_h
#define __slow_mem_h
#include <systemc.h>
#include "types.h"
#include "slave_if.h"
class slow_mem
  : public slave_if
  , public sc_module
{
public:
  // ports
  sc_in_clk clock;
  SC_HAS_PROCESS(slow_mem);
  // constructor
  slow_mem(sc_module_name name_
		      , unsigned int start_address
		      , unsigned int end_address
		      , unsigned int nr_wait_states)
    : sc_module(name_)
    , m_start_address(start_address)
    , m_end_address(end_address)
    , m_nr_wait_states(nr_wait_states)
    , m_wait_count(-1)
  {
    // process declaration
    SC_METHOD(wait_loop);
    dont_initialize();
    sensitive_pos << clock;

    sc_assert(m_start_address <= m_end_address);
    sc_assert((m_end_address-m_start_address+1)%4 == 0);
    unsigned int size = (m_end_address-m_start_address+1)/4;
    MEM = new int [size];
    for (unsigned int i = 0; i < size; ++i)
      MEM[i] = 0;
  }

  // destructor
  ~slow_mem();

  // process
  void wait_loop();

  // direct Slave Interface
  bool direct_read(int *data, unsigned int address);
  bool direct_write(int *data, unsigned int address);

  // Slave Interface
  status read(int *data, unsigned int address);
  status write(int *data, unsigned int address);

  unsigned int start_address() const;
  unsigned int end_address() const;

private:
  int *MEM;
  unsigned int m_start_address;
  unsigned int m_end_address;
  unsigned int m_nr_wait_states;
  int m_wait_count;

}; // end class slow_mem

inline  slow_mem::~slow_mem()
{
  if (MEM) delete [] MEM;
  MEM = (int *)0;
}

inline void slow_mem::wait_loop()
{
  if (m_wait_count >= 0) m_wait_count--;
}

inline bool slow_mem::direct_read(int *data, unsigned int address)
{
  *data = MEM[(address - m_start_address)/4];
  return true;
}

inline bool slow_mem::direct_write(int *data, unsigned int address)
{
  MEM[(address - m_start_address)/4] = *data;
  return true;
}

inline status slow_mem::read(int *data
						   , unsigned int address)
{
  // accept a new call if m_wait_count < 0)
  if (m_wait_count < 0)
    {
      m_wait_count = m_nr_wait_states;
      return TRANSFER_WAIT;
    }
  if (m_wait_count == 0)
    {
      *data = MEM[(address - m_start_address)/4];
      return TRANSFER_OK;
    }
  return TRANSFER_WAIT;
}

inline status slow_mem::write(int *data
						    , unsigned int address)
{
  // accept a new call if m_wait_count < 0)
  if (m_wait_count < 0)
    {
      m_wait_count = m_nr_wait_states;
      return TRANSFER_WAIT;
    }
  if (m_wait_count == 0)
    {
      MEM[(address - m_start_address)/4] = *data;
      return TRANSFER_OK;
    }
  return TRANSFER_WAIT;
}


inline unsigned int slow_mem::start_address() const
{
  return m_start_address;
}

inline unsigned int slow_mem::end_address() const
{
  return m_end_address;
}

#endif
