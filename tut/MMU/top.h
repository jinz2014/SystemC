#include "ram.h"
#include "mmu.h"
#include "master.h"

class top : public sc_module {
  public:
    sc_in_clk clk;

    ram<int> m0;
    /*
    ram<int> m1;
    ram<int> m2;
    ram<int> m3;
    */

    Master u1;
    mmu<int> mmu1;

    top(sc_module_name name) :

      sc_module(name), 

      m0("RAM0", 0,     0xff), 
      /*
      m1("RAM1", 0x100, 0x1ff), 
      m2("RAM2", 0x200, 0x2ff), 
      m3("RAM3", 0x300, 0x3ff), 
      */
      mmu1("MMU") ,
      u1("Master") {
      
        mmu1.ram_port(m0);
        /*
        mmu1.ram_port(m1);
        mmu1.ram_port(m2);
        mmu1.ram_port(m3);
        */

        u1.clk             (clk);
        u1.multi_ram_port  (mmu1);
      }

};


