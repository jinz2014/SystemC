/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2004 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.4 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/


#ifndef BUS_TYPES_HEADER
#define BUS_TYPES_HEADER

#include "pipelined_protocol.h"

using pipelined_protocol::address_phase_request;
using pipelined_protocol::address_phase_status;
using pipelined_protocol::data_phase_request;
using pipelined_protocol::data_phase_response;

using tlm::tlm_transport_if;

typedef unsigned int ADDRESS_TYPE;
typedef unsigned int DATA_TYPE;

typedef tlm_transport_if< address_phase_request< ADDRESS_TYPE > ,
                          address_phase_status > address_if;

typedef tlm_transport_if< data_phase_request< DATA_TYPE > ,
                          data_phase_response< DATA_TYPE > > data_if;

#endif
