#include "systemc.h"
SC_MODULE (jkff) {
sc_in<bool> j, k, set, reset;
sc_inout<bool> q; //����Ϊinout�ͣ��Զ���qֵ
sc_in<bool> clk; //ʱ�Ӷ˿�
// JK�������ķ���
void jk_flop ();
//������
SC_CTOR (jkff) {
SC_METHOD (jk_flop);
sensitive_pos << clk;
sensitive_neg << set; 
sensitive_neg<<reset;
}
};
void jkff::jk_flop() {
sc_uint<2> temp; //����temp�������������ƶ˿�J��K��ֵ
if (reset.read()==0){
q.write(0); // ��λ
}else if (set.read()==0){
q.write(1); // ��λ
}else {
temp[1] = j.read();
temp[0] = k.read();
switch(temp) {
case 0x1: q.write(0); // д0
break;
case 0x2: q.write(1); // д1
break;
case 0x3: // ��ת
q.write(!q.read());
break;
default: break; // ����
}
}
}
