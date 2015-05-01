#include "systemc.h"


SC_MODULE(fun)
{
  // ports
  //
  sc_inslave<int, sc_memenHandshake<int,1,1> > op1;
  sc_inslave<int, sc_memenHandshake<int,1,1> > op2;
  sc_inslave<int, sc_memenHandshake<int,1,1> > cmd;
  sc_outslave<int, sc_memenHandshake<int,1,1> > result;

  sc_in_clk clk;
  sc_in<int> rstp;

  // sc_bit s;
  
  int operand1;
  int operand2;
  int command;
  int x;
  
  void fun_thread ()
    {
      while(1)
      {
      wait();

      if (rstp == 0) 
	{
	  operand1 = 0;
	  operand2 = 0;
	  command = 1;
	  result.d = 0;
	}
      else 
	{
	  if (op1.en == true) 
	      operand1 = op1.d;	// read operand 1

	  if (op2.en == true) 
	      operand2 = op2.d;       	// read operand 2

	  if (cmd.en == true) 
	      command = cmd.d;		// read command

	  if (result.en == true) 
	    {
	      switch (command) 
		{
		case 1 :
		  result.d = x = operand1 + operand2;	// Add
                  cout << "cmd = ADD " << "  op1 = " << operand1;
                  cout << "  op2 = " << operand2 << "  result = " << x << endl;

		  // s = x;
		  // result.d = s;
		  // cout << "value of terminal d = " << s << endl;
		  // result.d = x;

		  break;
		case 2 :
		  result.d = x = operand1 - operand2;	// Subtract
                  cout << "cmd = SUB " << "  op1 = " << operand1;
                  cout << "  op2 = " << operand2 << "  result = " << x << endl;
		  break;		  
		case 3 :
		  result.d = x = operand1 * operand2;	// Multiply
                  cout << "cmd = MUL " << "  op1 = " << operand1;
                  cout << "  op2 = " << operand2 << "  result = " << x << endl;
		  break;	      
		default :
		  cout <<  "\n fun: Undefined operation\n" << endl;
		  break;
		}
	    }
	}
      }
    }

  // constructor
  SC_CTOR(fun)
    {
      SC_THREAD(fun_thread)
      sensitive << clk;
    }
};
