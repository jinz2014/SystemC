#include "init_packet.h"

void init_packet::prc_init_packet() {
  packet temp;

  if (send) {
    temp.packet_id = XMIT_ID;
    temp.packet_st = xmit;
  }
  else {
    temp.packet_id = DONE_ID;
    temp.packet_st = done;
  }

  tsq = temp;
}

