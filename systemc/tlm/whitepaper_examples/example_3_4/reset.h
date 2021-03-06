/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2004 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.4 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/


#ifndef RESET_HEADER
#define RESET_HEADER

#include <systemc.h>

class reset : public sc_module
{
public:
  reset( sc_module_name module_name , int reset_cycles = 1 );
  
  SC_HAS_PROCESS( reset );

  sc_in<bool> clk;
  sc_out<bool> rst;

private:
  void run();

  int count , max_count;

};
#endif
