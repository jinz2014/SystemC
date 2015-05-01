#include "systemc.h"

# define idle      0
# define transmit  1


SC_MODULE(ctrl)
{
  // ports
  sc_inslave<int, sc_memfullHandshake<int,1,1> > cmd_in;
  sc_inmaster<int, sc_memenHandshake<int,1,1> > op1_in;
  sc_inmaster<int, sc_memenHandshake<int,1,1> > op2_in;
  
  sc_outmaster<int, sc_memenHandshake<int,1,1> > op1_out;
  sc_outmaster<int, sc_memenHandshake<int,1,1> > op2_out;
  sc_outmaster<int, sc_memenHandshake<int,1,1> > cmd_out;
  sc_inmaster<int, sc_memenHandshake<int,1,1> > result;

  sc_outmaster<int, sc_memenHandshake<int,1,1> > display;

  // sc_inslave<bool> rstp;
  // sc_inslave<bool> clk;
  //
  sc_in_clk clk;
  sc_in<int> rstp;

  // sc_logic y;
  
  static int state;

  void ctrl_thread ()    
  {
      while(1)      
      {
      wait();
      // assigning logic value to ack
      // y = 'Z'; 
      // cmd_in.ack = y;
      // cout << " Assigned logic value Z to ack =   " << y << endl;

      cmd_in.ack=false;
      if (rstp == 0)
	{
	  state = idle;
	  cmd_in.ack = false;
	}
      else	
      {
	
	  if (cmd_in.req == true)
	    {
	      //convert req bit to string
	      //cout << "req terminal = " << cmd_in.req.to_string() << endl; 
	      //state = transmit;
	      cmd_out.en = true;
	      
	      op1_in.en = true;
	      op2_in.en = true;
	      op1_out.en = true;
	      op2_out.en = true;
	      result.en = true;
	      display.en = true;
	      
	      
	      int x = cmd_in.d;
	      cmd_out.d = x;
	      //  cout << "cmd =   "<< x ;

	      x = op1_in.d;
	      op1_out.d = x;
	      // cout << " op1 = "<< x;

	      x = op2_in.d;
	      op2_out.d = x;
	      // cout << " op2 = "<< x << endl;

	      x = result.d;
	      display.d = x;	        
	      // cout << "    Result = " << x << endl;
	      //cmd_in.ack = true;
	    }		  
	  else {
	    int x = result.d;
	    display.d = x;
	    //  cout << "    Result2 = " << x << endl;          
	  }
         }
      }
  }
        
  // constructor of the module 
  SC_CTOR(ctrl)
    {
      SC_THREAD(ctrl_thread);
      sensitive << clk;
    }
  
};
