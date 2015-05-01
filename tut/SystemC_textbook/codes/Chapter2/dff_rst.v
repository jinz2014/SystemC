module dff_rst(clk, rst, din, dout);
 input clk, rst, din;
 output dout;
 reg dout;
always @(posedge clk or posedge rst) begin
  if (rst) dout <= 1¡¯b0;
  else dout = din;
end
endmodule

#include <systemc.h>
SC_MODULE(dff_rst)
{
sc_in<bool> clock;
sc_in<bool> reset;
sc_in<bool> din;
sc_out<bool> dout;
void do_it()
{
if (reset) {
dout = false;
} else if (clock.event()) {
dout = din;
}
};
SC_CTOR(dff_rst)
{
SC_METHOD(do_it);
sensitive_pos(reset);
sensitive_pos(clock);
}
};