#include "systemc.h"
#include "sc_mslib.h"
#include "key.h"
#include "ctrl.h"
#include "fun.h"
#include "disp.h"
#include "reset.h"


int key::array1[MYMAX] = {1,2,3,4,5 };
int key::array2[MYMAX] = {1,3,5,7,9 };
int ctrl::state=0;
int reset::count=0;

int sc_main(int argc, char* argv[])
{
  sc_link_mp<int> cmd;
  sc_link_mp<int> in1;
  sc_link_mp<int> in2;
  sc_link_mp<int> op1out;
  sc_link_mp<int> op2out;
  sc_link_mp<int> cmd_out;
  sc_link_mp<int> result;
  sc_link_mp<int> display;
  
  sc_signal<int> rst;

  sc_clock CLOCK("clock",5);

  reset r1("reset");
  r1.clk(CLOCK);
  r1.rstp(rst);
   
  key k1("key");
  k1.cmd(cmd);
  k1.op1(in1);
  k1.op2(in2);
  k1.clk(CLOCK);
  k1.rstp(rst);
  
  ctrl c1("ctrl");
  c1.cmd_in(cmd);
  c1.op1_in(in1);
  c1.op2_in(in2);
  c1.op1_out(op1out);
  c1.op2_out(op2out);
  c1.cmd_out(cmd_out);
  c1.result(result);
  c1.display(display);  
  c1.clk(CLOCK);
  c1.rstp(rst);

  fun f1("fun");
  f1.op1(op1out);
  f1.op2(op2out);
  f1.cmd(cmd_out);
  f1.result(result);
  f1.clk(CLOCK);
  f1.rstp(rst);

  disp d1("display");
  d1.din(display);
  d1.clk(CLOCK);
  d1.rstp(rst);

  sc_start(200);
  
  return (0);

};
