#ifndef _TB_H
#define _TB_H
#include "source.h"
#include "sink.h"

class tb: public sc_module {
  public:
    sc_clock clk;
    sc_fifo<char> fifo;
    source src ;
    sink   dst ;

  tb(sc_module_name name, int size) :
    sc_module(name),
    fifo("fifo", size),
    src("source") ,
    dst("sink") ,
    clk("clock", 10, SC_NS) {
      src.write_port(fifo) ;
      src.clk(clk) ;
      dst.read_port(fifo) ;
      dst.clk(clk) ;
    }
};
#endif
