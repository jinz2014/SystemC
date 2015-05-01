#include "systemc.h"	

SC_MODULE(disp)
{
  // ports
  
  sc_inslave<int, sc_memenHandshake<int,1,1> > din;
  sc_in_clk clk;
  sc_in<int> rstp;

  int myData;

  void disp_thread ()
    {
      while (1)
      {
      wait();
      if (rstp == 0) 
	{
	  myData = 0;
	} 
      else 
	{
	  
	  if (din.en == true) 
	    {
	      myData = din.d;
	    }
	}
      }
    }

 // constructor
 
 SC_CTOR(disp)
   {
     SC_THREAD(disp_thread)  
     sensitive << clk;		

     cout <<  " Tutorial - BCA Version - Results: " << endl;  
   }
};
