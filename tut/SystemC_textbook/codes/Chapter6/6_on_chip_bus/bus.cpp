
#include "bus.h"

void bus::end_of_elaboration()
{
  // perform a static check for overlapping memory areas of the slaves
  bool no_overlap;
  for (int i = 1; i < slave_port.size(); ++i) {
    slave_if *slave1 = slave_port[i];
    for (int j = 0; j < i; ++j) {
      slave_if *slave2 = slave_port[j]; 
      no_overlap = ( slave1->end_address() < slave2->start_address() ) ||
               ( slave1->start_address() > slave2->end_address() );
      if ( !no_overlap ) {
        sb_fprintf(stdout,"Error: overlapping address spaces of 2 slaves : \n");
        sb_fprintf(stdout,"slave %i : %0X..%0X\n",i,slave1->start_address(),slave1->end_address()); 
        sb_fprintf(stdout,"slave %i : %0X..%0X\n",j,slave2->start_address(),slave2->end_address());
        exit(0);
      }
    }
  }
}

//----------------------------------------------------------------------------
//-- process
//----------------------------------------------------------------------------

void bus::main_action()
{
  // m_current_request is cleared after the slave is done with a
  // single data transfer. Burst requests require the arbiter to
  // select the request again.

  if (!m_current_request)
    m_current_request = get_next_request();
  else
    // monitor slave wait states
    if (m_verbose)
      sb_fprintf(stdout, "%g SLV [%d]\n", sc_simulation_time(),
		 m_current_request->address);
  if (m_current_request)
    handle_request();
  if (!m_current_request)
    clear_locks();
}

//----------------------------------------------------------------------------
//-- direct BUS interface
//----------------------------------------------------------------------------

bool bus::direct_read(int *data, unsigned int address)
{
  if (address%4 != 0 ) {// address not word alligned
    sb_fprintf(stdout, "  BUS ERROR --> address %04X not word alligned\n",address);
    return false; 
  }
  slave_if *slave = get_slave(address);
  if (!slave) return false;
  return slave->direct_read(data, address);
}

bool bus::direct_write(int *data, unsigned int address)
{
  if (address%4 != 0 ) {// address not word alligned
    sb_fprintf(stdout, "  BUS ERROR --> address %04X not word alligned\n",address);
    return false; 
  }
  slave_if *slave = get_slave(address);
  if (!slave) return false;
  return slave->direct_write(data, address);
}

//----------------------------------------------------------------------------
//-- non-blocking BUS interface
//----------------------------------------------------------------------------

void bus::read(unsigned int unique_priority
		      , int *data
		      , unsigned int address
		      , bool lock)
{
  if (m_verbose)
    sb_fprintf(stdout, "%g %s : read(%d) @ %x\n",
	       sc_simulation_time(), name(), unique_priority, address);
  //If A new request is asserted,insert it to the tail of the queue   
  request *request = get_request(unique_priority);

  // abort when the request is still not finished
  sc_assert((request->status == TRANSFER_OK) ||
	    (request->status == TRANSFER_ERROR));

  request->do_write           = false; // we are reading
  request->address            = address;
  request->end_address        = address;
  request->data               = data;

  if (lock)
    request->lock = (request->lock == LOCK_SET) ? 
      LOCK_GRANTED : LOCK_SET;

  request->status = TRANSFER_REQUEST;
}

void bus::write(unsigned int unique_priority
		       , int *data
		       , unsigned int address
		       , bool lock)
{
  if (m_verbose) 
    sb_fprintf(stdout, "%g %s : write(%d) @ %x\n",
	       sc_simulation_time(), name(), unique_priority, address);

  request *request = get_request(unique_priority);

  // abort when the request is still not finished
  sc_assert((request->status == TRANSFER_OK) ||
	    (request->status == TRANSFER_ERROR));

  request->do_write           = true; // we are writing
  request->address            = address;
  request->end_address        = address;
  request->data               = data;

  if (lock)
    request->lock = (request->lock == LOCK_SET) ?
      LOCK_GRANTED : LOCK_SET;

  request->status = TRANSFER_REQUEST;
}

status bus::get_status(unsigned int unique_priority)
{
  return get_request(unique_priority)->status;
}

//----------------------------------------------------------------------------
//-- blocking BUS interface
//----------------------------------------------------------------------------

status bus::burst_read(unsigned int unique_priority
					 , int *data
					 , unsigned int start_address
					 , unsigned int length
					 , bool lock)
{
  if (m_verbose) 
    sb_fprintf(stdout, "%g %s : burst_read(%d) @ %x\n",
	       sc_simulation_time(), name(), unique_priority, start_address);
	
  request *request = get_request(unique_priority);

  request->do_write           = false; // we are reading
  request->address            = start_address;
  request->end_address        = start_address + (length-1)*4;
  request->data               = data;

  if (lock)
    request->lock = (request->lock == LOCK_SET) ? 
      LOCK_GRANTED : LOCK_SET;

  request->status = TRANSFER_REQUEST;

  wait(request->transfer_done);
  wait(clock->posedge_event());
  return request->status;
}

status bus::burst_write(unsigned int unique_priority
					  , int *data
					  , unsigned int start_address
					  , unsigned int length
					  , bool lock)
{
  if (m_verbose) 
    sb_fprintf(stdout, "%g %s : burst_write(%d) @ %x\n",
	       sc_simulation_time(), name(), unique_priority, start_address);
	
  request *request = get_request(unique_priority);

  request->do_write           = true; // we are writing
  request->address            = start_address;
  request->end_address        = start_address + (length-1)*4;
  request->data               = data;

  if (lock)
    request->lock = (request->lock == LOCK_SET) ? 
      LOCK_GRANTED : LOCK_SET;

  request->status = TRANSFER_REQUEST;

  wait(request->transfer_done);
  wait(clock->posedge_event());
  return request->status;
}

//----------------------------------------------------------------------------
//-- BUS methods:
//
//     handle_request()   : performs atomic bus-to-slave request
//     get_request()      : BUS-interface: gets the request form of given 
//                          priority
//     get_next_request() : returns a valid request out of the list of 
//                          pending requests
//     clear_locks()      : downgrade the lock status of the requests once
//                          the transfer is done
//----------------------------------------------------------------------------

void bus::handle_request()
{
  if (m_verbose)
      sb_fprintf(stdout, "%g %s Handle Slave(%d)\n",
		 sc_simulation_time(), name(), m_current_request->priority);

  m_current_request->status = TRANSFER_WAIT;
  slave_if *slave = get_slave(m_current_request->address);

  if ((m_current_request->address)%4 != 0 ) {// address not word alligned
    sb_fprintf(stdout, "  BUS ERROR --> address %04X not word alligned\n",m_current_request->address);
    m_current_request->status = TRANSFER_ERROR;
    m_current_request = (request *)0;
    return;
  }
  if (!slave) {
    sb_fprintf(stdout, "  BUS ERROR --> no slave for address %04X \n",m_current_request->address);
    m_current_request->status = TRANSFER_ERROR;
    m_current_request = (request *)0;
    return;
  }

  status slave_status = TRANSFER_OK;
  if (m_current_request->do_write)
    slave_status = slave->write(m_current_request->data, 
				m_current_request->address);
  else
    slave_status = slave->read(m_current_request->data,
			       m_current_request->address);

  if (m_verbose)
    sb_fprintf(stdout, "  --> status=(%s)\n", status_str[slave_status]);

  switch(slave_status)
    {
    case TRANSFER_ERROR:
      m_current_request->status = TRANSFER_ERROR;
      m_current_request->transfer_done.notify();
      m_current_request = (request *)0;
      break;
    case TRANSFER_OK:
      m_current_request->address+=4; //next word (byte addressing)
      m_current_request->data++;
      if (m_current_request->address > m_current_request->end_address)
	{
	  // burst-transfer (or single transfer) completed
	  m_current_request->status = TRANSFER_OK;
	  m_current_request->transfer_done.notify();
	  m_current_request = (request *)0;
	}
      else
	{ // more data to transfer, but the (atomic) slave transfer is done
	  m_current_request = (request *)0;
	}
      break;
    case TRANSFER_WAIT:
      // the slave is still processing: no clearance of the current request
      break;
    default:
      break;
    }
}

slave_if *bus::get_slave(unsigned int address)
{
  for (int i = 0; i < slave_port.size(); ++i)
    {
      slave_if *slave = slave_port[i];
      if ((slave->start_address() <= address) &&
	  (address <= slave->end_address()))
	return slave;
    }
  return (slave_if *)0;		
}

request * bus::get_request(unsigned int priority)
{
  request *ptr_request = (request *)0;
  for (int i = 0; i < m_requests.size(); ++i)
    {
      ptr_request = m_requests[i];
      if ((ptr_request) &&
	  (ptr_request->priority == priority))
	return ptr_request;
    }
  ptr_request = new request;
  //cout<<"new request status:"<<ptr_request->status<<endl;
  ptr_request->priority = priority;
  m_requests.push_back(ptr_request);
  return ptr_request;		
}

request * bus::get_next_request()
{
  // the slave is done with its action, m_current_request is
  // empty, so go over the bag of request-forms and compose
  // a set of likely requests. Pass it to the arbiter for the
  // final selection
  request_vec Q;
  for (int i = 0; i < m_requests.size(); ++i)
    {
      request *request = m_requests[i];
      if ((request->status == TRANSFER_REQUEST) ||
	  (request->status == TRANSFER_WAIT))
	{
	  if (m_verbose) 
	    sb_fprintf(stdout, "%g %s : request (%d) [%s]\n",
		       sc_simulation_time(), name(), 
		       request->priority, status_str[request->status]);
	  Q.push_back(request);
	}
    }
  if (Q.size() > 0)
    return arbiter_port->arbitrate(Q);
  return (request *)0;
}

void bus::clear_locks()
{
  for (int i = 0; i < m_requests.size(); ++i)
    if (m_requests[i]->lock == LOCK_GRANTED)
      m_requests[i]->lock = LOCK_SET;
    else
      m_requests[i]->lock = LOCK_NO;
}
