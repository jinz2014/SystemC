#include "systemc.h"
SC_MODULE (dff) {
sc_in<bool> in_data, reset;
sc_out<bool> out_q;
sc_in<bool> clock; // ʱ�Ӷ˿�
void dff_pos ();
// ������
SC_CTOR (dff) {
SC_METHOD (dff_pos);
sensitive_pos << clock << reset;
}
};
void dff:: dff_pos () {
if (reset.read()){
out_q.write(0);
}else{
out_q.write(in_data.read());
}
}
