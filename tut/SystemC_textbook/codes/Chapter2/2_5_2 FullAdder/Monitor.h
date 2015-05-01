// File monitor.h
//Chenxi,2003.5.24
#ifndef __MONITOR_H
#define __MONITOR_H
#include "systemc.h"
SC_MODULE(Monitor) {	
	sc_in<sc_bit> m_a,m_b,m_cin,m_sum, m_cout;
	
	void prc_monitor();
 
	SC_CTOR(Monitor) {
		SC_THREAD(prc_monitor);
		sensitive<<m_a,m_b,m_cin,m_sum,m_cout;
	}
};
#endif