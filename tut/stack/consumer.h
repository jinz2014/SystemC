#include "systemc.h"
#include "stack_if.h"

class consumer : public sc_module
{
public:

  sc_port<stack_read_if> in;
  sc_in<bool> Clock;

  void do_reads()
  {
    char c;
    while (true)
    {
      if (in->nb_read(c))
        cout << "R " << c << " at " << sc_time_stamp() << endl;
      wait();             // on clock edge
    }
  }

  SC_CTOR(consumer)
  {
    SC_THREAD(do_reads);
    sensitive << Clock.pos();
  }
};

