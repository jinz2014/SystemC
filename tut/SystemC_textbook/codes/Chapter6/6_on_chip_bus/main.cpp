
#include "systemc.h"
#include "test.h"

int sc_main(int, char **)
{
  test top("top");

  sc_start(100);

  return 0;
}
