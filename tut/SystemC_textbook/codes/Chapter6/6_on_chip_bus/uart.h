#ifndef _UART_H
#define _UART_H
#include "types.h"
#include "systemc.h"
#include "uart_logic.h"

class uart:public sc_module,public slave_if
{
public:
	sc_in_clk clk;
	sc_out<bool> txd;
	sc_in<bool> rxd;

  uart_logic *ul;   
  sc_fifo<sc_int<8> > *c_fifo;

	uart(sc_module_name name_
		,unsigned int start_address
		,unsigned int end_address)
		:sc_module(name_)
		
	{   
    c_fifo =new sc_fifo<sc_int<8> >;
		ul= new uart_logic("Uart_logic",start_address,end_address);
    ul->clk(clk);
    ul->read_port(*c_fifo);
    ul->rxfifo_write_port(*c_fifo);
    ul->txd(txd);
		ul->rxd(rxd);
	}

	~uart(){
		if(ul){delete ul; ul=0;}
		if(c_fifo){delete c_fifo;c_fifo=0;}
	}

   bool direct_read(int *data, unsigned int address);
   bool direct_write(int *data, unsigned int address);

  // Slave Interface
   status read(int *data, unsigned int address);
   status write(int *data, unsigned int address);

  unsigned int start_address() const;
  unsigned int end_address() const;
};


bool uart::direct_read(int *data, unsigned int address){
  return ul->direct_read(data,address);
}
bool uart::direct_write(int *data, unsigned int address){
  return ul->direct_write(data,address);
}
status uart::read(int *data, unsigned int address){
	return ul->read(data,address);
}
status uart::write(int *data, unsigned int address){
	return ul->write(data,address);
}
inline unsigned int uart::start_address() const
{
  return ul->start_address();
}

inline unsigned int uart::end_address() const
{
  return ul->end_address();
}
#endif
