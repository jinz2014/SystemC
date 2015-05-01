#include "systemc.h"
SC_MODULE( tristate ) {
sc_in<bool> in_sela, in_selb;
sc_in<sc_logic> in_a, in_b;
sc_out_rv<1> out_1;
// Method for first three-state driver
void tristate_a();
// Method for second three-state driver
void tristate_b();
// Constructor
SC_CTOR( tristate ) {
SC_METHOD( tristate_a);
sensitive << in_sela << in_a;
SC_METHOD( tristate_b);
sensitive << in_selb << in_b;
}
};
void tristate::tristate_a() {
if (in_sela.read()){
out_1.write(in_a.read());
}else{
out_1.write("Z");
}
}
void tristate::tristate_b() {
if (in_selb.read()){
out_1.write(in_b.read());
}else{
out_1.write("Z");
}
}
