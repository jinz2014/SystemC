#include "systemc.h"
#include "sc_mslib.h"

typedef int 	data_type;
int 		state=0;
bool 		bWrite=true;


SC_MODULE(testbench) {
  sc_in_clk driver;
  sc_signal<data_type> signal;

  void response( ) {
    static int x = 0;
    signal.write( x++ );
  }
  SC_CTOR( testbench ) {
    SC_METHOD( response );
    sensitive << driver;
  };
}; // testbench


SC_MODULE( mod2 ) {
  sc_inoutslave< data_type >	inouts;
  sc_inslave< data_type >	ins;
  sc_slave< data_type >		s;
  sc_outslave< data_type >	outs;

  // the slave functions
  void slave_func()	{ cout <<" slave function: "; }	

  void inslave_func()	{
    data_type x;
    x = ins;
    if(state)
      cout <<" reading inslave="<< x;
    else			    
      cout <<" #reading inslave="<< ins.read();
  }

  void outslave_func( ) {
    data_type x=81;
    if ( bWrite ) {
      if ( state ) {
	cout <<" writing outslave="<<x;
	outs=x;	 // propagate the value to master
      } else {
	cout <<"#writing outslave="<<x;
	outs.write(x);
      }
      bWrite=false;
    }
  }

  
  void inoutslave_func(){
    data_type x;
    x = inouts;
    if ( inouts->input() ) {
      if ( state )
	cout <<" reading inoutslave="<< x;
      else
	cout <<" #reading inoutslave="<< inouts.read();
    } else {
      data_type x=55;
      if ( bWrite ) {
	if ( state ) {
	  cout <<" Writing inoutslave="<< x;
	  inouts=x;
	} else {
	  cout<<"#Writing inoutslave="<< x;
	  inouts.write(x);
	}
	bWrite=false;
      }
    }
  }

  // constructor
  SC_CTOR( mod2 ) {
	  SC_SLAVE(slave_func,s);	

	  SC_SLAVE(inslave_func,ins);		

	  SC_SLAVE(outslave_func,outs);		

	  SC_SLAVE(inoutslave_func,inouts);		
  }
}; // mod2


SC_MODULE(mod1) {
  // input port, unrefinable, for stimulus
  sc_in<data_type> read_port;

  sc_master<data_type> m;
  sc_inmaster<data_type> inm;
  sc_outmaster<data_type> outm;
  sc_inoutmaster<data_type> inoutm;

  void master_func() {
    cout << endl <<"invoking master: ";
    m(); // invoke the slaves
    data_type x;

    cout << endl;
    x = 56;
    if ( bWrite ) {
      cout<< endl <<"writing inoutmaster= "<< x;
      if ( state )
	inoutm=x;
      else
	inoutm.write(x);
      bWrite = false;
    }

    cout<<endl;
    bWrite=true;
    if ( state ) {
      x=inm;
      cout << " reading inmaster=" << x << endl;
    } else {
      x = inm.read();
      cout << " #reading inmaster=" << x << endl;
    }

    x = 25;
    if ( bWrite ) {
      cout << endl << "writing outmaster=" << x;
      if ( state )
	outm=x;
      else
	outm.write(x);
      bWrite=false;
    }

    cout <<endl;
    bWrite=true;
    if ( state ) {
      x=inoutm;
      cout << " reading inoutmaster=" << x <<endl;
    } else {
      x = inoutm.read();
      cout << " #reading inoutmaster=" << x;
    }

    cout << endl;
  } // master_func

  SC_CTOR(mod1) {
    SC_METHOD(master_func);
    sensitive << read_port;
  }       
}; // mod1

int sc_main(int ac, char *av[] ) {
  sc_signal<data_type> sig;
  mod1 inst1("Master");
  mod2 inst2("Slave");
  sc_link_mp<data_type> ch;
  sc_clock clk("TestClock",5);

  testbench t("TestBench");
  t.driver( clk );

  // make the connections
  inst1.m(ch);
  inst2.s(ch);
  inst1.inm(ch);
  inst2.ins(ch);
  inst1.outm(ch);
  inst2.outs(ch);
  inst1.inoutm(ch);
  inst2.inouts(ch);

  inst1.read_port(t.signal);
  // inst2.b(sig);

  sc_start(50);

  cout << endl;
  return 0;
}
