/****cnt4.cpp 实现文件****/
#include "cnt4.h"
void cnt4::do_cnt4(){
	if(clear==1) //清零
		   dout = 0;
	else 
	  if(updown) 
		dout=dout.read()+1;//向上计数
	  else 
		dout=dout.read()-1; //向下计数
}
}；
