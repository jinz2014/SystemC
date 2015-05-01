#include "systemc.h"
SC_MODULE( d_latch ) {
sc_in<unsigned char> in_i;
sc_out<unsigned char> out;
void d_latch_fcn () {
switch (in_i.read()) {
case 0: out.write(0x01); break;
case 1: out.write(0x02); break;
case 2: out.write(0x04); break;
case 3: out.write(0x10); break;
case 4: out.write(0x20); break;
case 5: out.write(0x40); break;
}
}
SC_CTOR( d_latch ) {
SC_METHOD( d_latch_fcn);
sensitive (in_i);
}
};
