#include "master_blocking.h"

void master_blocking::main_action()
{
  const unsigned int mylength = 0x10; // storage capacity/burst length in words
  int mydata[mylength];
  unsigned int i;
  status status;

  while (true)
    {
      wait(); // ... for the next rising clock edge
      status = bus_port->burst_read(m_unique_priority, mydata, 
				    m_address, mylength, m_lock);
      if (status == ERROR)
	sb_fprintf(stdout, "%g %s : blocking-read failed at address %x\n",
		   sc_simulation_time(), name(), m_address);

      for (i = 0; i < mylength; ++i)
	{
	  mydata[i] += i;
	  wait();
	}

      status = bus_port->burst_write(m_unique_priority, mydata, 
				     m_address, mylength, m_lock);
      if (status == ERROR)
	sb_fprintf(stdout, "%g %s : blocking-write failed at address %x\n",
		   sc_simulation_time(), name(), m_address);

      wait(m_timeout, SC_NS);
    }
}
