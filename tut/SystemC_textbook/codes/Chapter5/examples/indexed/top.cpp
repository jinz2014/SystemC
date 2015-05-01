#include "systemc.h"
#include "sc_mslib.h"

typedef int data_type;

SC_MODULE(mod1) {
  // input port, unrefinable, for stimulus
  sc_in<data_type> a;
  // Refinable port
  sc_outmaster<data_type,sc_indexed<data_type,5> > P1[10];
  sc_inmaster<data_type,sc_indexed<data_type,5> > P2[10];

  void master_func() {
    static int x=0;
    static int y=0;

    P1[y][x] = a; // invoke the slaves

    data_type val;
    val = P2[y][x];

    cout << "after incrementing value="<<val << endl; 

    y = ( y+1 ) % 10;
    x = ( x+1 ) % 10;
  }

  void bindchannel(sc_link_mp<data_type>& ch) {
    int i;
    for ( i=0; i<10; i++ )
      P1[i].bind(ch);
    for ( i=0;i<10;i++ )
      P2[i](ch);
  }

  SC_CTOR(mod1) {
    //sc_async_fprocess(handle1,"Master",mod1,master_func);
    SC_METHOD(master_func);
    sensitive << a;

    end_module();
  }
};  // mod1

//--------------------------
SC_MODULE( mod2 ) {
  data_type b;
  sc_inslave<data_type,sc_indexed<data_type,5> > P2;
  sc_inoutslave<data_type,sc_indexed<data_type,5> > S;

  void slave_func() {  // for sc_inslave
    data_type b = P2;
    b = P2.read();
    cout << " obtained " << b << " from master, index = " << 
    P2.get_address() << endl;
  }

  // sc_outslave
  void slave_func2() {
    if ( !S->input() ) {
      data_type one(1);
      data_type val;

      val = S.read();

      val = val + one;	// hope this works for all data types;
      S.write(val);
    }
  }

  void f1() {
    cout << " #### " << endl;
  }

  SC_CTOR(mod2) :P2() {
    SC_SLAVE(slave_func,P2);
    SC_SLAVE(slave_func2,S);
  }
}; // mod2


SC_MODULE(testbench) {
  sc_in_clk driver;
  sc_out<int> write_port;

  void entry() {
    static int x=0;
    x +=1;
    write_port.write( x );
  }

  SC_CTOR( testbench ) {
    SC_METHOD( entry );
    sensitive << driver;
  }
};

int sc_main(int ac, char *av[] ) {
  sc_signal< data_type > sig;
  mod1 inst1("Master");
  mod2 inst2("Slave");
  sc_link_mp< data_type > ch;
  sc_clock clk("TestClock",5);

  testbench t("TestBench");

  inst1.bindchannel(ch);
  inst2.P2(ch);
  inst2.S(ch);

  t.write_port( sig );
  t.driver( clk );
  inst1.a(sig);
  // inst2.b(sig);
  sc_start(31);

  return 0;
}
