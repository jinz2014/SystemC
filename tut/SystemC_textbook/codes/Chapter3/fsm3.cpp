/***fsm3.cpp***/
#include "systemc.h"
#include "fsm3.h"
void ex_fsm::update_state() {
if (rst.read() == true) {
b.write(0);
a.write(0);
state = S0;
} else {
switch(state) {
case S0:
b.write(0);
if (input1.read() || input2.read())
a.write(1);
else
a.write(0);
if (input1.read() == 1)
state = S1;
break;
case S1:
a.write(0);
b.write(1);
if(input2.read() == 1)
state = S2;
break;
case S2:
a.write(0);
b.write(0);
state = S0;
break;
}
}
}
