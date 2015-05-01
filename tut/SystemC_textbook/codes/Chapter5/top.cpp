//
// top.cpp : contains sc_main ; Instantiates FIFO design
//
#ifndef SYSTEMC_H
#include "systemc.h"
#endif
#ifndef SC_XCOM_H
#include "sc_xcom.h"
#endif
#include "consumer.h"
#include "producer.h"
#include "fifo.h"
#ifndef BUFFER_H
#include "buffer.h"
#endif
int sc_main(int ac, char *av[] ){
// declare channels/signals
sc_link_mp<int> BW;
sc_link_mp<int> BR;
// create clocks with diff frequencies
sc_clock clock1 ("Clock1", 5, 0.5, 0.3,true);
sc_clock clock2 ("Clock2", 40, 0.5, 0.1,true);
// instantiate all blocks and connect to channels, signals
producer p1("Master");
fifo f1("fifo");
consumer c1("Slave");
p1.Pout(BW);
p1.clk(clock1);
f1.Pwrite(BW);
f1.Pread(BR);
c1.Cin(BR);
c1.clk(clock2);
sc_start(100);
// return zero if no error
return 0;
}
