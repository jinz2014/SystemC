/****xor_gates.cpp 实现文件****/
#include "xor_gates.h"
void xor_gates::prc_xor_gates(){
tap = bre.read() ^ sty.read();
// tap = bre ^ sty;
}
