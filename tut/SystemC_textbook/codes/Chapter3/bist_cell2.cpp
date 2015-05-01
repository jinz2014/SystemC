/****bist_cell.cpp 实现文件****/
#include "bist_cell.h"
void bist_cell::prc_bist_cell(){
bool s1, s2, s3;
s1 = !(b0&d1);
s2 = !(d0&b1);
s3 = !(s2|s1);
s2 = s2&s1;
z = !(s2|s3);
}
