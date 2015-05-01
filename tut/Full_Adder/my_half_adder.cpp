#include "my_half_adder.h"

// definition of add process
void my_half_adder::add () {
  co = x ^ y;
  s  = x & y;
}
