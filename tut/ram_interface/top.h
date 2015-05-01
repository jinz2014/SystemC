#include "ram.h"
#include "master.h"

class top : public sc_module {
  public:
    sc_in_clk clk;
    ram<int> m1;
    Master u1;
    top(sc_module_name name) :
      sc_module(name), 
      m1("RAM", 0, 1000), 
      u1("bsm") {
        u1.clk         (clk);
        u1.ram_port    (m1);
      }
};


