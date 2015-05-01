// File: monitor.cpp
#include "monitor.h"
void Monitor::prc_monitor(){
	while(1){
	cout << "At time " <<sc_time_stamp() << "::";
	cout <<"(a,b,carry_in): ";	
	cout <<m_a.read()<<m_b.read()<<m_cin.read()<<",";
	cout << "(sum,carry_out): ";
	cout << m_sum.read() << m_cout.read() << endl;
	wait();
	}
}
