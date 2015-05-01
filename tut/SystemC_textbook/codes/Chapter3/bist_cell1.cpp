/****bist_cell.cpp 实现文件****/
#include "bist_cell.h"
void bist_cell::prc_bist_cell(){
z = !(!(d0&b1)&!(b0&d1))|!(!(d0&b1)|!(b0&d1));
}
