 
# define ADD 1
# define SUBTRACT 2
# define MULTIPLY 3
# define MYMAX 5

SC_MODULE(key)
{

  // ports
  sc_outmaster<int, sc_memfullHandshake<int,1,1> > cmd;
  sc_outslave<int, sc_memenHandshake<int,1,1> > op1;
  sc_outslave<int, sc_memenHandshake<int,1,1> > op2;

  sc_in_clk    clk;
  sc_in<int>   rstp;

  static int array1[MYMAX];
  static int array2[MYMAX];
  
  int i, state;

  void key_thread ()  {
    
    while (1) {
      wait();
      
      if (rstp == 0) {
	state = i = 0;
	cmd.d = 1;
	cmd.req = false;
      }
      else {
	switch (state) {
	case 0:
	  cmd.req = false;
	  if (cmd.ack == false) 
	      state = 1;
	  else 
	    state = 0;
	  break;
	case 1:
	  cmd.req = true;
	  cmd.d = ADD;
	  state = 2;
	  break;
	case 2:
	  cmd.req = true;
	  cmd.d = SUBTRACT;
	  state = 3;
	  break;
	case 3:
	  cmd.req = true;
	  cmd.d = MULTIPLY;
	  state = 0;
	  break;
	}          
	  
	if (op1.en == true)
	  {
	    if (i == MYMAX-1)
	      i = 0;
	    else
	      i++ ;
	    op1.d = array1[i];
	  }
	if (op2.en == true)
	  {
	    op2.d = array2[i];
	  }
      }
    }
  }

  // constructor
  SC_CTOR(key) : cmd(), op1(), op2() {
      SC_THREAD(key_thread);
      sensitive << clk;
    }
};
