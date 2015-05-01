#include "systemc.h"
template <class T>
class sc_signal_in_if
: virtual public sc_interface
{
  public:
    virtual const T& read() const = 0;
}

template <class T>
class sc_signal_inout_if
: virtual public sc_signal_in_if<T>
{
  public:
    virtual void write(const T&) = 0;
}

template <class T>
class sc_signal 
: public sc_prim_channel,
  public sc_signal_inout_if <T>
{
  public:

    virtual const T& read() const {
      return m_cur_val;
    }

    virtual const sc_event& default_event() const {
      return m_value_changed_event;
    }

    virtual void write(const T& value) {
      if (current_process() != m_driver ) {
        if (m_driver == 0)
          m_driver = current_process();
        else
          error("more than one driver");
      }

      m_new_val = value;

      if (m_new_val != m_cur_val)
        request_update();
    }
}


