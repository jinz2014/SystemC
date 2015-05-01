#include "systemc.h"
SC_MODULE( sr_latch ) {
sc_in<bool> reset, set;
sc_out<bool> q;
void do_sr_latch () {
if (reset.read() == 0)
q.write(0);
else if (set.read() == 0)
q.write(1);
}
SC_CTOR( sr_latch ) {
SC_METHOD( do_sr_latch);
sensitive << reset << set;
}
};
