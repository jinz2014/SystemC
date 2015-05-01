#include "driver.h"
#include "monitor.h"
#include "shifter.h"
#include "parameter.h"

int sc_main(int argc, char* argv[]) {

  sc_signal<sc_int<WORD> > t_data_in;
  sc_signal<sc_uint<BITS> > t_num_bits;
  sc_signal<sc_int<WORD> > t_data_out;

  /*
  shifter s ("shifter");
  s.data_in(t_data_in);
  s.num_bits(t_num_bits);
  s.data_out(t_data_out);
  */

  shifter *s = new shifter("shifter");
  s->data_in(t_data_in);
  s->num_bits(t_num_bits);
  s->data_out(t_data_out);
  

  driver d ("GenerateStimulus");
  d.d_data_in(t_data_in);
  d.d_num_bits(t_num_bits);

  monitor m ("MonitorResults");
  m.m_data_in(t_data_in);
  m.m_num_bits(t_num_bits);
  m.m_data_out(t_data_out);

  sc_start(200, SC_NS);

  delete s;

  sc_start(-1);

  return 0;
}
