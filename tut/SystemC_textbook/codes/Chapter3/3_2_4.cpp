//´®ÐÐÒÆÎ»¼Ä´æÆ÷1

#include "systemc.h"
SC_MODULE(rtl_nb) {
sc_in<bool> clk;
sc_in<bool> data;
sc_inout<bool> regc, regd;
void reg_proc() {
regc.write(data.read());
regd.write(regc.read());
}
SC_CTOR(rtl_nb) {
SC_METHOD(reg_proc);
sensitive_pos << clk;
}
};
