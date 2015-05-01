

#include "arbiter.h"

request *
arbiter::arbitrate(const request_vec &requests)
{
  int i;
  // at least one request is here
  request *best_request = requests[0]; 

  if (m_verbose) 
    { // shows the list of pending requests
      sb_fprintf(stdout, "%g %s :", sc_simulation_time(), name());
      for (i = 0; i < requests.size(); ++i)
	{
	  request *request = requests[i];
          // lock_status encoding
          const char lock_chars[] = { '-', '=', '+' };
          // status encoding
           sb_fprintf(stdout, "\n    R[%d](%c%s@%x)",
                     request->priority,
                     lock_chars[request->lock],
                     status_str[request->status],
                     request->address);
	}
    }

  // highest priority: status==WAIT and lock is set: 
  // locked burst-action
  for (i = 0; i < requests.size(); ++i)
    {
      request *request = requests[i];
      if ((request->status == TRANSFER_WAIT) &&
	  (request->lock == LOCK_SET))
	{
	  // cannot break-in a locked burst
	  if (m_verbose)
            sb_fprintf(stdout, " -> R[%d] (rule 1)\n", request->priority);
	  return request;
	}
    }

  // second priority: lock is set at previous call, 
  // i.e. LOCK_GRANTED
  for (i = 0; i < requests.size(); ++i)
    if (requests[i]->lock == LOCK_GRANTED)
      {
	if (m_verbose)
	  sb_fprintf(stdout, " -> R[%d] (rule 2)\n", requests[i]->priority);
	return requests[i];
      }

  // third priority: priority
  for (i = 1; i < requests.size(); ++i)
    {
      sc_assert(requests[i]->priority != best_request->priority);
      if (requests[i]->priority < best_request->priority)
	best_request = requests[i];
    }

  if (best_request->lock != LOCK_NO)
    best_request->lock = LOCK_GRANTED;
	
  if (m_verbose) 
    sb_fprintf(stdout, " -> R[%d] (rule 3)\n", best_request->priority);

  return best_request;
}
