/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2002 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.3 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  main.cpp - This file instantiates all processes and ties them together
             with signals.

  Original Author: Rashmi Goswami, Synopsys, Inc.

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/
#include "systemc.h"
#include "pkt.h"
#include "switch_clk.h"
#include "sender.h"
#include "receiver.h"
#include "switch.h"
#include "statistics_gen.h"

int
sc_main(int argc, char *argv[])
{
  sc_signal<pkt> pkt_in0;
  sc_signal<pkt> pkt_in1;
  sc_signal<pkt> pkt_in2;
  sc_signal<pkt> pkt_in3;
  sc_signal<pkt> pkt_out0;
  sc_signal<pkt> pkt_out1;
  sc_signal<pkt> pkt_out2;
  sc_signal<pkt> pkt_out3;
 
  sc_signal<sc_int<4> > id0, id1, id2, id3;
  sc_signal<int> d0;
  sc_signal<int> d1;
  sc_signal<int> d2;
  sc_signal<int> d3;
  sc_signal<int> d4;
  sc_signal<int> d5;  
  sc_signal<bool> switch_cntrl;

  sc_clock clock1("CLOCK1", 75, 0.5, 0.0);
  sc_clock clock2("CLOCK2", 30, 0.5, 10.0);

  // Module instiatiations follow
  // Note that modules can be connected by hooking up ports 
  // to signals by name or by using a positional notation

  sender sender0("SENDER0");
  // hooking up signals to ports by name
  sender0.pkt_out(pkt_in0);
  sender0.source_id(id0);
  sender0.CLK(clock1);

  sender sender1("SENDER1");
  // hooking up signals to ports by position
  sender1 << pkt_in1 << id1 << clock1;

  sender sender2("SENDER2");
  // hooking up signals to ports by name
  sender2.pkt_out(pkt_in2);
  sender2.source_id(id2);
  sender2.CLK(clock1);

  sender sender3("SENDER3");
  // hooking up signals to ports by position
  sender3 << pkt_in3 << id3 << clock1;
  
  switch_clk switch_clk1("SWITCH_CLK");
  // hooking up signals to ports by name
  switch_clk1.switch_cntrl(switch_cntrl);
  switch_clk1.CLK(clock2);

  mcast_pkt_switch switch1("SWITCH");
  // hooking up signals to ports by name
  switch1.switch_cntrl(switch_cntrl);
  switch1.in0(pkt_in0);
  switch1.in1(pkt_in1);
  switch1.in2(pkt_in2);
  switch1.in3(pkt_in3);
  switch1.out0(pkt_out0);
  switch1.out1(pkt_out1);
  switch1.out2(pkt_out2);
  switch1.out3(pkt_out3);
  switch1.q0_pntr(d0);
  switch1.q1_pntr(d1);
  switch1.q2_pntr(d2);
  switch1.q3_pntr(d3);
  switch1.drop_cnt(d4);
  switch1.switched_cnt(d5);
  statistics_gen t("Display");  
  t.ctrl(switch_cntrl);
  t.din0(d0);
  t.din1(d1);
  t.din2(d2);
  t.din3(d3);
  t.din5(d4);
  t.din4(d5);
  receiver receiver0("RECEIVER0");
  // hooking up signals to ports by name  
  receiver0.pkt_in(pkt_out0);
  receiver0.sink_id(id0);

  receiver receiver1("RECEIVER1");
  // hooking up signals to ports by position
  receiver1 << pkt_out1 << id1;

  receiver receiver2("RECEIVER2");
  // hooking up signals to ports by name
  receiver2.pkt_in(pkt_out2);
  receiver2.sink_id(id2);

  receiver receiver3("RECEIVER3");
  // hooking up signals to ports by position
  receiver3 << pkt_out3 << id3;

  sc_initialize();

#if !defined(__SUNPRO_CC)
  id0.write(0); 
  id1.write(1);
  id2.write(2);
  id3.write(3);
#else
  // you cannot do that with SC5.0
  // since it doesn't support member templates
  id0.write(sc_int<4>(0));
  id0.write(sc_int<4>(1));
  id0.write(sc_int<4>(2));
  id0.write(sc_int<4>(3));
#endif
   //<TRACE>
  sc_trace_file *tf = sc_create_vcd_trace_file("pkt_switch");
  sc_trace(tf,switch_cntrl,"SWITCH_CNTRL");
  sc_trace(tf,clock1,"CLK1");
  sc_trace(tf,clock2,"CLK2");
  sc_trace(tf, pkt_in0, "PKT_IN0");
  sc_trace(tf, pkt_in1, "PKT_IN1");
  sc_trace(tf, pkt_in2, "PKT_IN2");
  sc_trace(tf, pkt_in3, "PKT_IN3");
  
  sc_trace(tf, pkt_out0, "PKT_OUT0");
  sc_trace(tf, pkt_out1, "PKT_OUT1");
  sc_trace(tf, pkt_out2, "PKT_OUT2");
  sc_trace(tf, pkt_out3, "PKT_OUT3");
  //</TRACE>

  sc_clock::start(-1);
  return 0;

}

