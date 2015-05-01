#include "memory.h"

void memory::prc_memory() {
  sc_lv<WORD_SIZE> allzs (sc_logic_Z);
  sc_lv<WORD_SIZE> allxs (sc_logic_X);

  if (en) {
    if (rw) { // read
      if (addr.read() < MEM_SIZE) 
        data = ram[addr.read()];
      else {
        data = allxs;

    #ifndef SYNTHESIS
        cout << "Read address " << addr << " is out of range" << endl;
    #endif
      }
    }
    else { // write
      if (addr.read() < MEM_SIZE) 
        ram[addr.read()] = data;
      else {
        data = allxs;
    #ifndef SYNTHESIS
        cout << "Write address " << addr << " is out of range" << endl;
    #endif
      }
    }
  }
  else 
    data = allzs;
}


