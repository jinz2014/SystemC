#include "systemc.h"
SC_MODULE( d_latch ) {
sc_in<bool> in_data;
sc_in<bool> clock;
sc_out<bool> out_q;
void do_d_latch () {
out_q.write(1); // …Ë÷√ƒ¨»œ÷µ
if (clock.read())
out_q.write(in_data.read());
}
SC_CTOR( d_latch ) {
SC_METHOD( do_d_latch);
sensitive << in_data << clock;
}
};
