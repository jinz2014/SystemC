//By Chenxi,2003.3.15
//----------------
//simple SOC
//----------------
#include <systemc.h>
#include "cpu.h"
#include "memoryunit.h"
#include "gpio.h"
#include "dma.h"
SC_MODULE(simple_soc){
  CPU *cpu1;
  MemoryUnit *mu1;
  GPIO   *gpio1;
  DMA    *dma1;
  //Constructor
  SC_CTOR(simple_soc){
  cpu1 = new CPU("CPU");
  mu1  = new MemoryUnit("MU");
  gpio1= new GPIO("GPIO");
  dma1 = new DMA("DMA");
  }
  //Destructor
  ~simple_soc(){
  if(cpu1) {delete cpu1; cpu1 =0;}
  if(mu1)  {delete mu1;  mu1  =0;}
  if(gpio1){delete gpio1;gpio1=0;}
  if(dma1) {delete dma1; dma1 =0;}
  }
};