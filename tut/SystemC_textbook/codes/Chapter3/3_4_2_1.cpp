#include "systemc.h"
SC_MODULE( tristate ) {
sc_in<bool> control;
sc_in<sc_logic> data;
sc_out<sc_logic> ts_out;
// 三态缓冲器的方法
void do_tristate () {
if (control.read()){
ts_out.write(data.read());
}else{
ts_out.write('Z');
}
}
// 构造器
SC_CTOR( tristate ) {
SC_METHOD( do_tristate);
sensitive << control << data;
}
};
