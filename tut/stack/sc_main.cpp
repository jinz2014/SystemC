#include "systemc.h"
#include "producer.h"
#include "consumer.h"
#include "stack.h"

int sc_main(int argc, char* argv[])
{
    sc_clock ClkFast("ClkFast", 50, SC_NS);
    sc_clock ClkSlow("ClkSlow", 100, SC_NS);

    stack Stack1("stack");

    producer P1("producer");
    P1.out(Stack1);
    P1.Clock(ClkFast);

    consumer C1("consumer");
    C1.in(Stack1);
    C1.Clock(ClkSlow);

    sc_start(5000, SC_NS);

    sc_start(-1);
    return 0;
}
