/****xor_gates.cpp ʵ���ļ�****/
#include "xor_gates.h"
void xor_gates::prc_xor_gates(){
tap = bre.read() ^ sty.read();
// tap = bre ^ sty;
}
