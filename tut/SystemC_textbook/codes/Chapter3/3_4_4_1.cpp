#include "systemc.h"
enum state_t { //利用枚举类型建立状态变量
S0, S1, S2
};
SC_MODULE(ex_fsm){
sc_in_clk clk;
sc_in<bool> rst, input1, input2;
sc_out<bool> a, b;
sc_signal<state_t> state, next_state;
void ns_op_logic();
void update_state();
SC_CTOR(ex_fsm){
SC_METHOD(update_state);
sensitive_pos << clk;
SC_METHOD(ns_op_logic);
sensitive << state << input1 << input2;
}
};
void ex_fsm::update_state() {
if (rst.read() == true)
state = S0;
else
state = next_state;
}
void ex_fsm::ns_op_logic() {
// 状态转移和输出逻辑
switch(state) {
case S0:
b.write(0);
if (input1.read() || input2.read())
a.write(1);
else
a.write(0);
if (input1.read() == 1)
next_state = S1;
else
next_state = S0;
break;
case S1:
a.write(0);
b.write(1);
if (input2.read() == 1)
next_state = S2;
else
next_state = S0;
break;
case S2:
a.write(0);
b.write(0);
next_state = S0;
break;
default:
a.write(0);
b.write(0);
next_state = S0;
break;
}
}
