#include "systemc.h"
#include "sc_mslib.h"
SC_MODULE(producer){
sc_outmaster<int> out1;
sc_in<bool> start; //����producer���̵��ź�
void generate_data (){
for (int i = 0; i < 10; i++){
out1 = i ; // ���ôӽ���
}
}
SC_CTOR(producer){
SC_METHOD(generate_data);
sensitive << start;
}
};
SC_MODULE(consumer){
sc_inslave<int> in1;
int sum; // ����Ϊģ���״̬
void accumulate (){
sum += in1;
cout << "Sum = " << sum << endl;
}
SC_CTOR(consumer){
sc_slave(accumulate, in1);
sum = 0; // ���ۼ������г�ʼ��
}
};
SC_MODULE(top) { // ����ģ��
producer *A1;
consumer *B1;
sc_link_mp<int> link1;
SC_CTOR(top){
A1 = new producer("A1");
A1->out1(link1);
B1 = new consumer("B1");
B1->in1(link1);
}
};
