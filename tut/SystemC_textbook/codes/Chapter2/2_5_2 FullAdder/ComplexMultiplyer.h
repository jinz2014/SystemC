// ComplexMultiplyer header file
//calculate (a + ib)(c + id) = (ac - bd) + i(ad + bc)
#include "systemc.h"
SC_MODULE(ComplexMultiplyer) {
// Declare ports
sc_in<bool> reset;
sc_in<bool> new_data;
sc_in<sc_int<8> > data_in;
sc_in_clk clk;
sc_out<bool> ready_for_data;
sc_out<bool> output_data_ready;
sc_out<sc_int<16> > real_out;
sc_out<sc_int<16> > imag_out;
// Declare internal variables and signals
// Declare processes in the module
void entry();
// Constructor
SC_CTOR (ComplexMultiplyer) {
// Register processes and define active clock edge
SC_CTHREAD(entry, clk.pos());
// Watching for global reset
watching(reset.delayed() == true);
}
};

/*********************************/
// ComplexMultiplyer.cc implementation file
#include "systemc.h"
#include "ComplexMultiplyer.h"
void ComplexMultiplyer :: entry()
{
sc_int<8> a, b, c, d;
//Initialize and reset if reset asserts
ready_for_data.write(false);
output_data_ready.write(false);
real_out.write(0);
imag_out.write(0);
wait(); //need clock to initialize before while loop
while (true)
{
ready_for_data.write(true);
output_data_ready.write(false);
wait_until(new_data.delayed() == true);
ready_for_data.write(false);
// Read four data values from input port
a = data_in.read();
wait();
b = data_in.read();
wait();
c = data_in.read();
wait();
d = data_in.read();
wait();
//Calculate and write output ports
real_out.write(a * c - b * d);
imag_out.write(a * d + b * c);
output_data_ready.write(true);
wait();
}
}