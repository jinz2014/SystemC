#include "master.h"


void Master::main_action() {
  wait();
  int i = 0;
  address = 0;

  while (i++ < 100) {
    data = rand();

    if (ram_port->write(address, data) == TRANSFER_OK) {
      cout << "write address " << address << " data " << data << endl;
    } 
    else cout << "Error: RAM write address " << address << endl;

    if (ram_port->read(address, data) == TRANSFER_OK) {
      cout << "read address " << address << " data " << data << endl;
    } 
    else cout << "Error: RAM read address " << address << endl;

    wait();
    address++;
  }
}
