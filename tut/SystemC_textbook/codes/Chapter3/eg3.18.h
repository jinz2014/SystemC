/****eg3.18.h****/
#include "systemc.h"
SC_MODULE(cnt) {
sc_in<bool> clk;
sc_in<bool> reset;
sc_out<sc_uint<4> > count_out;
sc_uint<4> count; // 数据成员变量
SC_CTOR(cnt) {
SC_METHOD(do_count);
sensitive_pos << clk;
sensitive_neg << reset;
SC_METHOD(outregs);
sensitive_pos << clk;
sensitive_neg << reset;
}
void do_count() {
if (reset.read() == 0)  count = 0;
else  count++;
}
void outregs() {
if (reset.read() == 0) count_out.write(0);
else count_out.write(count);
}
};
