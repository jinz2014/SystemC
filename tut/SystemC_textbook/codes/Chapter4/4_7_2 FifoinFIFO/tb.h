#ifndef _TB_H
#define _TB_H
#include <systemc.h>
#include "fifo_hl.h"
#define PERIOD 20
class source : public sc_module
{
  public:
	sc_in_clk clk;
    sc_port<sc_fifo_out_if<char> > write_port;
    sc_port<reset_if> reset_port;
    SC_HAS_PROCESS(source);

    source(sc_module_name name) : sc_module(name)
    {SC_CTHREAD(main,clk.neg());}

    void main()
    {
      int i=0;      
      const char str []=
        "For any problems,feel free to contact the author via Email:chenxiee@mails.tsinghua.edu.cn!\n";      
      reset_port->reset(75);	         
	  wait();
      while (true)
      {
        if (rand() & 1)
        { if (str[i]) {write_port->write(str[i++]);} }
        wait();
      }
    }
};

class sink : public sc_module
{
  public:
    sc_in_clk clk;
    sc_port<sc_fifo_in_if<char> > read_port;

    SC_HAS_PROCESS(sink);

    sink(sc_module_name name) : sc_module(name)
    {
      SC_CTHREAD(main,clk.neg());
    }

    void main()
    {
      char c;      
      while (true) {
        if (rand() & 1)
        {
          read_port->read(c);cout << c;
        }
        wait();
      }
    }
};

class tb : public sc_module
{
  public:
    fifo_hl<char> fifo1;
    source source1;
    sink sink1;
    sc_clock clk;
    
    tb(sc_module_name name, int size) :
        sc_module(name) ,
        fifo1("Fifo1", size) , 
        source1("source1") , 
        sink1("sink1"),
        clk("Clk",PERIOD,SC_NS)
    {
	  
      source1.write_port(fifo1);
      source1.reset_port(fifo1);
	  source1.clk(clk);
      sink1.read_port(fifo1);
	  sink1.clk(clk);
      fifo1.clk(clk);
    }  
};
#endif