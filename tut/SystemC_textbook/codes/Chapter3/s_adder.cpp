/****s_adder.cpp ʵ���ļ�****/
#include "s_adder.h"
void s_adder_c::prc_s_adder_c(){
 	sc_int<5> temp;	
	temp = a.read() + b.read();
	sum = temp.range(3,0);
	carry_out = temp[4];
}
