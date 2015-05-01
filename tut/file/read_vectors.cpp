#include "read_vectors.h"

void read_vectors::prc_read_vectors() {
  int  t_d1, t_d2, t_sel;

  if (infile >> t_sel >> t_d1 >> t_d2) {
    cout << "Reading " << t_sel
         << " " << t_d1
         << " " << t_d2 << endl;
    read_sel_op = t_sel;
    read_data1  = t_d1;
    read_data2  = t_d2;
  }
  else {
    sc_stop();
  }
}

