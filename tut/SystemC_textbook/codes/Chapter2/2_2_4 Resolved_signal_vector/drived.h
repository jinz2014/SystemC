#ifndef __DRIVED_H
#define __DRIVED_H
#include <systemc.h>
SC_MODULE(Drived){
sc_in_rv<1>  result;
//sc_signal<sc_logic> temp;
void display(){
	/*
	switch(temp.write(result.read())) {
	case '0': cout<<"At time:"<<sc_simulation_time()<<",result changed to 0"<<endl;
				  break;
    case '1': cout<<"At time:"<<sc_simulation_time()<<",result changed to 1"<<endl;
				  break;
    case 'X': cout<<"At time:"<<sc_simulation_time()<<",result changed to X"<<endl;
				  break;
    default:cout<<"At time:"<<sc_simulation_time()<<",result changed to Z"<<endl;

	}
	*/
};
SC_CTOR(Drived){
	SC_METHOD(display);
	sensitive<<result;
}
};
#endif