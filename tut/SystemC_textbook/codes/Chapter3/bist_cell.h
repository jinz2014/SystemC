/****bist_cell.h 头文件****/
#include "systemc.h"
SC_MODULE(bist_cell) {
sc_in<bool> b0,b1,d0,d1;
sc_out<bool> z;
void prc_bist_cell();
SC_CTOR(bist_cell) {
	SC_METHOD(prc_bist_cell);
	sensitive <<b0<<b1<<d0<<d1;//组合逻辑的输入端
}
};
