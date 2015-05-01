#include "systemc.h"

SC_MODULE(reset)
{
  
  sc_in_clk     clk;
  sc_out<int>  rstp;   
  
  static int count;

  void reset_thread ()
    { 
      rstp = 0;
      while(1) 
      {
        wait();
        if (count == 5)
	  {
  	  rstp = 0;
          //cout << "count = " << count << endl;
	  }
        else if (count == 7)
        {
	  rstp = 1;
          //cout << "count = " << count << endl;

        }
        if (count <= 7)
  	  count++;
      }
    }

    // constructor
    SC_CTOR(reset)
    {
      SC_THREAD(reset_thread)
      sensitive << clk;
    }
};
