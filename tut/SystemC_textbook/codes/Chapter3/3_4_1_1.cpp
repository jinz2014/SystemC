#include "systemc.h"
SC_MODULE (dff) {
sc_in<bool> in_data; // ����˿�
sc_out<bool> out_q; // ����˿�
sc_in<bool> clock; // ʱ�Ӷ˿�
// D�������ķ���
void dff_pos ();
// ������
SC_CTOR (dff) {
SC_METHOD (dff_pos);
sensitive_pos << clock;
}
};
void dff:: dff_pos(){
out_q.write(in_data.read());
}
