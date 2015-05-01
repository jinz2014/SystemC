
// fifo_hl<T>: hierarchical channel that implements the
// sc_fifo<T> interfaces. Uses embedded fifo_ca to implement
// FIFO, and has a clock input port to drive the fifo_ca.
#ifndef _FIFO_HL_H
#define _FIFO_HL_H
#include <systemc.h>
#include "fifo_ca.h"
#include "reset_if.h"
template <class T>
class fifo_hl
: public sc_module,
  public sc_fifo_in_if<T>,
  public sc_fifo_out_if<T>,
  public reset_if
{
public:
  sc_in<bool>     clk;
  sc_signal<T>    write_data;
  sc_signal<bool> write_enable;  
  sc_signal<bool> rst;
  sc_signal<T>    read_data;
  sc_signal<bool> read_enable;
  sc_signal<bool> full,empty;
  sc_signal<unsigned int> data_count;
  
  //FIFO in FIFO, fifo_ca1 is an embedded channel
  fifo_ca<T> fifo_ca1;
private:
  unsigned m_size;//actual size of FIFO
public:

  fifo_hl(sc_module_name name, unsigned size)
   : sc_module(name), fifo_ca1("fifo_ca1", size+1),m_size(size)
  {
	assert(m_size>0);  
    fifo_ca1.clk(clk);
	fifo_ca1.rst(rst);

    fifo_ca1.din (write_data);
    fifo_ca1.wr_en (write_enable);
    

    fifo_ca1.dout (read_data);
    fifo_ca1.rd_en(read_enable);

    fifo_ca1.full(full);
	fifo_ca1.empty(empty);
    fifo_ca1.data_count(data_count);
    write_enable.write(false);
	read_enable.write(false);
  }
  
  virtual void write(const T& data)
  {
    write_data = data;
    do {
      wait(clk->posedge_event());
    } while (full == true);
	wait(clk->posedge_event());
	write_enable = true;
	wait(clk->posedge_event());	
    write_enable = false;

  }

  virtual T read()
  {
	do {
      wait(clk->posedge_event());
    } while (empty == true);
	//wait(1,SC_NS);
	read_enable = true;
	wait(clk->posedge_event());	
	read_enable = false;
	wait(clk->negedge_event());    
    return read_data.read();
  }

  virtual void read(T& d) { d = read(); }  

  virtual bool nb_read(T& data) { 
      wait(clk->posedge_event());
      if (empty == true) return false;
	  else{
		  read_enable = true;
	      wait(clk->posedge_event());
	      wait(clk->posedge_event());
          read_enable = false;
          data=read_data.read();
		  return true;
	  } 

  }

  virtual bool nb_write(const T&) { 
	  if(full==true) return false; 
	  else{
        write_enable = true;
	    wait(clk->posedge_event());
        write_enable = false;
		return true;
	  }
  }

  virtual int num_available() const {
	  return (int) data_count;
  }

  virtual int num_free() const { 
	 
     return m_size-data_count;
  }

  virtual const sc_event& data_read_event() const
	{ assert(0); return read_enable.posedge_event(); 
  }

  virtual const sc_event& data_written_event() const
	{ assert(0); return write_enable.posedge_event();
  }

  //reset_if method  
  void reset(unsigned int interval){
      rst=true;
      wait(interval);
      rst=false;
      wait(clk.posedge_event());
  }

};

#endif

