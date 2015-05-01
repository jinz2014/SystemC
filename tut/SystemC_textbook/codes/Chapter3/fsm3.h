/***fsm3.h***/
enum state_t { //利用枚举类型建立状态变量
S0, S1, S2
};
SC_MODULE(ex_fsm){
sc_in_clk clk;
sc_in<bool> rst, input1, input2;
sc_out<bool> a, b;
sc_signal<state_t> state;
void update_state();
SC_CTOR(ex_fsm){
SC_METHOD(update_state);
sensitive_pos << clk;
}
};
