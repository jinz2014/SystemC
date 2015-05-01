#ifndef __request_h
#define __request_h

enum lock_status { LOCK_NO = 0
			      , LOCK_SET
			      , LOCK_GRANTED 
};

struct request
{
  // parameters
  unsigned int priority;

  // request parameters
  bool do_write;
  unsigned int address;
  unsigned int end_address;
  int *data;
  lock_status lock;

  // request status
  sc_event transfer_done;
  status status;

  // default constructor
  request();
};

inline request::request()
  : priority(0)
  , do_write(false)
  , address(0)
  , end_address(0)
  , data((int *)0)
  , lock(LOCK_NO)
  , status(TRANSFER_OK)
{}

#endif
