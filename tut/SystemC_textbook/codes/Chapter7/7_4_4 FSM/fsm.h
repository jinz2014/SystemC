//By chenxi,2003.5.5
//fsm.h
#ifndef _FSM_H
#define _FSM_H
#include <systemc.h>
enum syn_state { LOST,PRE_SYN,SYN};
template<int N1=3,int N2=5>
class fsm:public sc_module{
public:
sc_in_clk clk;
sc_in<bool> rst,detect;
sc_out<bool> syn_ind;
sc_signal<syn_state> next_state,state;
sc_signal<int> N1_counter,N2_counter;
void getnextst();
void setstate();
void assign_output();
void count_N1();
void count_N2();
SC_CTOR(fsm)
{
 SC_METHOD(getnextst);
 sensitive << state << detect << N1_counter << N2_counter;

 SC_METHOD(setstate);      sensitive_pos<< clk <<rst;
 SC_METHOD(assign_output); sensitive    << state;
 SC_METHOD(count_N1);      sensitive_pos<< clk;
 SC_METHOD(count_N2);      sensitive_pos<< clk;
};
};
#endif
template<int N1,int N2>
void fsm<N1,N2>::setstate(){
	if (rst== true) next_state.write(LOST);
	else state.write(next_state.read());
}

template<int N1,int N2>
void fsm<N1,N2>::getnextst(){
	switch (state){
	case  LOST:
		    if(detect==true) next_state=PRE_SYN;
			else next_state=LOST;
			break;
    case  PRE_SYN:
		    if(detect!=true) next_state=LOST;
			else if (N1_counter==N1) next_state=SYN;
			else next_state=PRE_SYN;
			break;
    case SYN:
		if(N2_counter==N2) next_state=LOST;
	     else next_state=SYN;
		 break;
    default:next_state=LOST; 
		 break;
	}
}

template<int N1,int N2>
void fsm<N1,N2>::assign_output(){
	syn_ind.write(state==SYN);
}

template<int N1,int N2>
void fsm<N1,N2>::count_N1(){
	if(state==PRE_SYN) {
		if(detect==true) {
       if(N1_counter<N1) N1_counter=N1_counter+1;
		}
		else N1_counter=0;
	}
	else N1_counter=0;
}

template<int N1,int N2>
void fsm<N1,N2>::count_N2(){
if(state==SYN) {
		if(detect!=true) {
       if(N2_counter<N2) N2_counter=N2_counter+1;
		}
		else N2_counter=0;
	}
	else N2_counter=0;
}
//End of file
