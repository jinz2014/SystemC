#include "systemc.h"
SC_MODULE( d_latch ) {
sc_in<bool> in_data;
sc_in<bool> clock;
sc_out<bool> out_q;
// 方法进程
void do_d_latch () {
if (clock.read())
{out_q.write(in_data.read());}
}
// 构造器
SC_CTOR( d_latch ) {
SC_METHOD( do_d_latch);
sensitive << in_data << clock;
}
};
