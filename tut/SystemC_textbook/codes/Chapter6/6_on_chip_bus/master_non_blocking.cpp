
#include "master_non_blocking.h"

void master_non_blocking::main_action()
{
  int mydata;
  int cnt = 0;
  unsigned int addr = m_start_address;

  wait(); // ... for the next rising clock edge
  while (true)
    {
      bus_port->read(m_unique_priority, &mydata, addr, m_lock);
      while ((bus_port->get_status(m_unique_priority) != TRANSFER_OK) &&
	     (bus_port->get_status(m_unique_priority) != TRANSFER_ERROR))
	wait();
      if (bus_port->get_status(m_unique_priority) == TRANSFER_ERROR)
	sb_fprintf(stdout, "%g %s : ERROR cannot read from %x\n",
		   sc_simulation_time(), name(), addr);

      mydata += cnt;
      cnt++;

      bus_port->write(m_unique_priority, &mydata, addr, m_lock);
      while ((bus_port->get_status(m_unique_priority) != TRANSFER_OK) &&
	     (bus_port->get_status(m_unique_priority) != TRANSFER_ERROR))
	wait();
      if (bus_port->get_status(m_unique_priority) == TRANSFER_ERROR)
	sb_fprintf(stdout, "%g %s : ERROR cannot write to %x\n",
		   sc_simulation_time(), name(), addr);
 
      wait(m_timeout, SC_NS);
      wait(); // ... for the next rising clock edge

      addr+=4; // next word (byte addressing)
      if (addr > (m_start_address+0x80)) {
        addr = m_start_address; cnt = 0;
      }
    }
}
