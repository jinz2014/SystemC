//Uart,Designed By Chenxi
#ifndef _UART_LOGIC_H
#define _UART_LOGIC_H
#include <systemc.h>
#include "types.h"
class uart_logic:public slave_if,public sc_module
{
public:
	sc_in_clk clk;
	sc_out<bool> txd;
	sc_in<bool> rxd;
	sc_port<sc_fifo_in_if<sc_int<8> > > read_port;
  sc_port<sc_fifo_out_if<sc_int<8> > > rxfifo_write_port;    

	 //receive logic
	SC_HAS_PROCESS(uart_logic);
    
	uart_logic(sc_module_name name_
		,unsigned int start_address
		,unsigned int end_address)
		:sc_module(name_)
		,m_start_address(start_address)
		,m_end_address(end_address)
		,status(0)
		,config(0)
	{
		SC_METHOD(receive_logic);		
		sensitive_pos<<clk;	

  
		 
	//	sc_assert(m_start_address <= m_end_address);
    //   sc_assert((m_end_address-m_start_address+1)%4 == 0);
		
	}  
   //
  void receive_logic();
	// direct Slave Interface
  bool direct_read(int *data, unsigned int address);
  bool direct_write(int *data, unsigned int address);

  // Slave Interface
  status read(int *data, unsigned int address);
  status write(int *data, unsigned int address);

  unsigned int start_address() const;
  unsigned int end_address() const;
  
  
private:
	unsigned int m_start_address,m_end_address;
	
	int status;
	int config;
};

inline bool uart_logic::direct_read(int *data, unsigned int address)
{
   return (read(data, address) == TRANSFER_OK);
}

inline bool uart_logic::direct_write(int *data, unsigned int address)
{
  return (write(data, address) == TRANSFER_OK);
}

inline status uart_logic::read(int *data , unsigned int address)
{
	if( address<m_start_address || address>m_end_address){
		*data =0;
    return TRANSFER_ERROR;
	}

  switch(address-m_start_address){
	  case STATUS_PORT:*data=status;return TRANSFER_OK;break;         
    case CONFIG_PORT:*data=config;return TRANSFER_OK;break;
    default:
	    sc_int<8> temp;   
        if(read_port->nb_read(temp)){*data = temp;return TRANSFER_OK;}
        else {return TRANSFER_ERROR;}
	 	break;
    }
  return TRANSFER_ERROR; 
}

inline status uart_logic::write(int *data
						    , unsigned int address)
{
  if( address<m_start_address || address>m_end_address)     
  return TRANSFER_ERROR; 
  
  return TRANSFER_OK;
}

inline unsigned int uart_logic::start_address() const
{
  return m_start_address;
}

inline unsigned int uart_logic::end_address() const
{
  return m_end_address;
}
void uart_logic::receive_logic(){
	//char received_data;
	//logic
	//if one byte data is properly received,then 
	//rxfifo_write_port->nb_write(received_data);
	};
#endif
