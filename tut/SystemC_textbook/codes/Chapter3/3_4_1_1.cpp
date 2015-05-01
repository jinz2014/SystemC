#include "systemc.h"
SC_MODULE (dff) {
sc_in<bool> in_data; // 输入端口
sc_out<bool> out_q; // 输出端口
sc_in<bool> clock; // 时钟端口
// D触发器的方法
void dff_pos ();
// 构造器
SC_CTOR (dff) {
SC_METHOD (dff_pos);
sensitive_pos << clock;
}
};
void dff:: dff_pos(){
out_q.write(in_data.read());
}
