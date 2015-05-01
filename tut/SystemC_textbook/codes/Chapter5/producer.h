//
// producer.h :: producer
//
#ifndef SYSTEMC_H
#include "systemc.h"
#endif
#ifndef SC_XCOM_H
#include "sc_xcom.h"
#endif
SC_MODULE(producer){
// port declaration
sc_in<int> full;
sc_outmaster<int> Pout; // refinable port
sc_in_clk clk;
// Internal variable
int val;
// outmaster process
void producer_thread(){
while (true){
val += 2;
Pout = val;
wait(); // wait for pos_edge clock event
}
}
SC_CTOR(producer){
SC_THREAD(producer_thread);
sensitive_pos << clk;
val = 0;
}
};
