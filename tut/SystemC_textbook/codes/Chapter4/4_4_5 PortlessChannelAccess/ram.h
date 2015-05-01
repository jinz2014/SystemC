// By Chenxi,2003.2.25
// ----------------------
// CHANNEL : ram
// ----------------------
#ifndef _RAM_H
#define _RAM_H
#include "systemc.h"
#include "mem_if.h"

template <class T>
class ram : public sc_module,ram_if<T> 
{
public:
 ram(sc_module_name name_, unsigned int start_address, unsigned int end_address)
	 :sc_module(name_)
	 ,m_start_address(start_address)
	 ,m_end_address(end_address){

	 sc_assert(end_address>=start_address);
     mem =new T[end_address-start_address];
 }

 ~ram(){ 
	 if(mem) {delete mem; mem=0;}
 }

 transfer_status read( unsigned address, T& data )
{
 if( address<m_start_address || address>m_end_address){
		data=0;  
		return TRANSFER_ERROR;
 }
 data = mem[address - m_start_address];
 return TRANSFER_OK;
}

 transfer_status write( unsigned address, T& data )
{
	if( address<m_start_address || address>m_end_address){	
      return TRANSFER_ERROR;}
	mem[address-m_start_address]=data;
	return TRANSFER_OK;
}

bool reset(){
	for (int i=0;i<(m_end_address-m_start_address);i++)
		mem[i]=(T)0;
	return true;
}

inline unsigned int start_address()const{
  return m_start_address;
} 

inline unsigned int end_address() const {
	return m_end_address;
}

private:
   T* mem;
   unsigned int m_start_address,m_end_address;
};
#endif



