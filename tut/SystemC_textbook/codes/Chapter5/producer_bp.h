//
// producer_bp.h :: producer with fullHandshake protocol
//
#include "systemc.h"
SC_MODULE(producer){
// internal variable
int val;
int state; // state variable of FSM
// port declaration
sc_outmaster<int, sc_fullHandshake<int> > Pout; // bus port
sc_in_clk clk;
// outmaster process
void producer_thread(){
state = 0;
Pout.req = 0;
while (true){
wait();
switch(state){
case 0:
Pout.req = 0;
if (Pout.ack == 0){
state = 1;
}
break;
case 1:
Pout.req = 1;
val += 2;
Pout.d = val;
state = 2;
break;
case 2:
if (Pout.ack==1){
state = 0;
Pout.req = 0;
}
break;
}
}
}
SC_CTOR(producer){
SC_THREAD(producer_thread);
sensitive_pos << clk;
val = 0;
}
};

