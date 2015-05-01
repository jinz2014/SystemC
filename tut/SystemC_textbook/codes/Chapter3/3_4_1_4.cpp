#include "systemc.h"
SC_MODULE (jkff) {
sc_in<bool> j, k;
sc_inout<bool> q; // 声明为inout型，以读入q值
sc_in<bool> clk; // 时钟端口
// JK触发器的方法
void jk_flop ();
// 构造器
SC_CTOR (jkff) {
SC_METHOD (jk_flop);
sensitive_pos << clk;
}
};
void jkff::jk_flop() {
sc_uint<2> temp; //利用temp来读入两个控制端口J和K的值
temp[1] = j.read( );
temp[0] = k.read( );
switch(temp) {
case 0x1: q.write(0); // 写0
break;
case 0x2: q.write(1); // 写1
break;
case 0x3: // 翻转
q.write(!q.read());
break;
default: break; // 不变
}
}
