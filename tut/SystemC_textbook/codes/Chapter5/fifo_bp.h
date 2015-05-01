// File Name : fifo_bp.h
// A module with inslave and outslave fullHandshake bus ports,
// and a fifo store
#include "systemc.h"
#ifndef BUFFER_H
#include "buffer.h"
#endif
SC_MODULE(fifo){
// ports
sc_in_clk wclk;
sc_in_clk rclk;
sc_inslave<int, sc_fullHandshake<int> > Pwrite; // slave port
sc_outslave<int, sc_fullHandshake<int> > Pread; // slave port
buffer<int> buf;
int item;
// slave methods
void blockingWrite(){
Pwrite.ack = 0;
while(1){
wait(); // wait for wclk
if (Pwrite.req){
if (buf.full() ){
// wait for buffer not full;
do {wait(); } // wait for wclk
while( buf.full());
}
item = Pwrite.d; // read from slave port
cout << "Writing into buffer: item = " << item << endl;
buf.put(item);
Pwrite.ack = 1;
while(Pwrite.req == 1)
wait(); // wait for wclk
Pwrite.ack = 0;
}
}
}
void blockingRead(){
Pread.ack = 0;
while(1){
wait(); // wait for clock
if (Pread.req){
cout << "\nfifo:blockingRead called" << endl;
if (buf.empty()){ // wait for not empty buffer
do {wait();} // wait for rclk
while (buf.empty() );
}
item = buf.get();
// cout << " Item read = " << item << endl;	
Pread.d = item; // write to slave port
Pread.ack = 1;
while(Pread.req == 1)
wait(); //wait for rclk
Pread.ack = 0;
}
}
}
SC_CTOR(fifo){
SC_THREAD(blockingWrite);
sensitive_pos << wclk;
SC_THREAD(blockingRead);
sensitive_pos << rclk;
}
};