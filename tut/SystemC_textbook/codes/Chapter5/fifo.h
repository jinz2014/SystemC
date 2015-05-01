// File Name : fifo.h
#ifndef SYSTEMC_H
#include "systemc.h"
#endif
#ifndef SC_XCOM_H
#include "sc_xcom.h"
#endif
#ifndef BUFFER_H
#include "buffer.h"
#endif
SC_MODULE(fifo){
// ports
sc_out<int> full;
sc_out<int> empty;
sc_inslave<int> Pwrite; // slave port
sc_outslave<int> Pread; // slave port
buffer<int> buf; // FIFO buffer
int item; // buffer item
// slave methods
void blockingWrite(){
if (buf.full() ){
do {wait();} // wait for sensitive edge of the producer clock
while( buf.full());	
// buffer is not full
// write into buffer
item = Pwrite; // read from slave port
cout << "Writing into buffer: item = " << item << endl;
buf.put(item);
}
void blockingRead(){
cout << "\nfifo:blockingRead called" << endl;
if (buf.empty()){
do {wait();} // wait for sensitive edge of the consumer clock
while (buf.empty() );
}
// buffer is not empty
// read from buffer
item = buf.get();
cout << " Item read = " << item << endl;
Pread = item; // write to slave port
}
SC_CTOR(fifo){
sc_slave( blockingWrite, Pwrite);
sc_slave ( blockingRead, Pread);
}
};
