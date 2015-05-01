//A "hello,SystemC!" system program
//By Chenxi,Copyright reserved 2003.3.21
#ifndef _HELLO_H
#define _HELLO_H
#include "systemc.h"
SC_MODULE(hello){
SC_CTOR(hello){ 
	cout<<"Hello,SystemC!"<<endl;
}
};
#endif


