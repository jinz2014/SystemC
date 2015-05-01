#include "driver.h"

void tb_driver::driver () {
  while (1) {
    data = rand() % 2;
    wait();
  }
}
