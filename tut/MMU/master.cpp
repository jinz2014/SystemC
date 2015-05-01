#include "master.h"


void Master::main_action() {
  wait();
  int i = 0;
  address = 0;

  while (i++ < 1) {
    data = rand();
    address = rand() % 1024;

    if (multi_ram_port->write(address, data) == TRANSFER_OK) {
      cout << " write address " << address << " data " << data << endl;
    } 
    else cout << "Error: RAM write address " << address << endl;

    if (multi_ram_port->read(address, data) == TRANSFER_OK) {
      cout << " read address " << address << " data " << data << endl;
    } 
    else cout << "Error: RAM read address " << address << endl;

    wait();
  }
}
