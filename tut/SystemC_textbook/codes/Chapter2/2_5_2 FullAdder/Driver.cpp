// File: driver.cpp
#include "driver.h"
void Driver::prc_driver(){
	sc_uint<3> pattern;	
	pattern=0;
	if(rst.read()==true) pattern=0;
	while(1) {
        
		d_a.write((sc_bit)pattern[0]);
		d_b.write((sc_bit)pattern[1]);
		d_cin.write((sc_bit)pattern[2]);		
		W_BEGIN
		watching(display_debug.delayed()==false);
        W_DO
		cout<<"Driver::"<<pattern;
		cout<<"a="<<d_a.read()<<",";
		cout<<"b="<<d_b.read()<<",";
        cout<<"ci="<<d_cin.read()<<endl;
		W_ESCAPE
        if(display_debug.read()==false) //only one watching condition,this line is useless
			cout<<"Debug Information is switched off"<<endl;
		W_END
		wait();		
		pattern++;
	}
}
