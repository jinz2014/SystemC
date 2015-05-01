//´®ÐÐÒÆÎ»¼Ä´æÆ÷2
#include "systemc.h"
SC_MODULE(rtl_b) {
sc_in<bool> clk;
sc_in<bool> data;
sc_out<bool> rega, regb;
bool rega_v, regb_v;
void reg_proc() {
rega_v = data.read();
regb_v = rega_v;
rega.write(rega_v);
regb.write(regb_v);
}
SC_CTOR(rtl_b) {
SC_METHOD(reg_proc);
sensitive_pos << clk;
}
};
