//
// consumer.h :: consumer module
//
#ifndef SYSTEMC_H
#include "systemc.h"
#endif
#ifndef SC_XCOM_H
#include "sc_xcom.h"
#endif
SC_MODULE(consumer){
// declare ports
sc_in<int> empty;
sc_inmaster<int> Cin;
sc_in_clk clk;
// Internal variable
int x;
// inmaster process
void consumerFunc(){
while (true){
x = Cin;
wait(); // wait for pos_edge clk
}
}
SC_CTOR(consumer){
SC_THREAD(consumerFunc);
sensitive_pos << clk;
}
};
