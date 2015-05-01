#include "systemc.h"
enum state_t { // enumerate states
S0, S1, S2
};
SC_MODULE(fsm){
sc_in_clk clk;
sc_in<bool> rst, input1, input2;
sc_out<bool> a, b;
sc_signal<state_t> state, next_state;
void ns_op_logic();
void output_logic();
void update_state();
SC_CTOR(fsm){
SC_METHOD(update_state);
sensitive_pos << clk;
SC_METHOD(ns_op_logic);
sensitive << state << input1 << input2;
SC_METHOD(output_logic);
sensitive << state << input1 << input2;
}
};

void fsm::update_state() {
if (rst.read() == true)
state = S0;
else
state = next_state;
}
void fsm::ns_op_logic() { // 决定下一个状态
switch(state) {
case S0:
if (input1.read() == 1)
next_state = S1;
else
next_state = S0;
break;
case S1:
if (input2.read() == 1)
next_state = S2;
else
next_state = S0;
break;
case S2:
next_state = S0;
break;
default:
next_state = S0;
break;
}
}
void fsm::output_logic() // 状态机输出
{
a.write(state == S0 && (input1.read()|| input2.read() ) );
b.write(state == S1);
}
