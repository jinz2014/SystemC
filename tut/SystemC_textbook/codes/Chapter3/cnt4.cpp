/****cnt4.cpp ʵ���ļ�****/
#include "cnt4.h"
void cnt4::do_cnt4(){
	if(clear==1) //����
		   dout = 0;
	else 
	  if(updown) 
		dout=dout.read()+1;//���ϼ���
	  else 
		dout=dout.read()-1; //���¼���
}
}��
