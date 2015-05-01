
#ifndef __test_h
#define __test_h

#include <systemc.h>

#include "master_blocking.h"
#include "master_non_blocking.h"
#include "master_direct.h"
#include "slow_mem.h"
#include "bus.h"
#include "fast_mem.h"
#include "arbiter.h"
#include "uart.h"
#include "test.h"

SC_MODULE(test)
{
  // channels
  sc_clock C1;

  // module instances
  master_blocking     *master_b;
  master_non_blocking *master_nb;
  master_direct       *master_d;
  slow_mem            *mem_slow;
  bus                 *m_bus;
  fast_mem            *mem_fast;
  arbiter             *m_arbiter;
  uart                *m_uart;
  sc_signal<bool>         rxd;
  sc_signal<bool>        txd;
  // constructor
  SC_CTOR(test)
    : C1("C1",10)
  {
    // create instances
    master_b = new master_blocking("master_b", 4, 0x4c, true, 300);
    master_nb = new master_non_blocking("master_nb", 3, 0x38, true, 20);
    master_d = new master_direct("master_d", 0x78, 100,true);
    mem_fast = new fast_mem("mem_fast", 0x00, 0x7f);
    mem_slow = new slow_mem("mem_slow", 0x80, 0xff, 1);
	m_uart   = new uart("UART",256,512);
    // bus = new simple_bus("bus",true); // verbose output
    m_bus = new bus("bus",true);
    // arbiter = new arbiter("arbiter",true); // verbose output
    m_arbiter = new arbiter("arbiter",true);

    // connect instances
    master_d->clock(C1);
    m_bus->clock(C1);
    master_b->clock(C1);
    master_nb->clock(C1);
    mem_slow->clock(C1);
    master_d->bus_port(*m_bus);
    master_b->bus_port(*m_bus);
    master_nb->bus_port(*m_bus);
    m_bus->arbiter_port(*m_arbiter);
    m_bus->slave_port(*mem_slow);
    m_bus->slave_port(*mem_fast);
	m_bus->slave_port(*m_uart);
	m_uart->clk(C1);
    m_uart->txd(txd);
    m_uart->rxd(rxd);
  }

  // destructor
  ~test()
  {
    if (master_b) {delete master_b; master_b = 0;}
    if (master_nb) {delete master_nb; master_nb = 0;}
    if (master_d) {delete master_d; master_d = 0;}
    if (mem_slow) {delete mem_slow; mem_slow = 0;}
    if (m_bus)    {delete m_bus; m_bus = 0;}
    if (mem_fast) {delete mem_fast; mem_fast = 0;}
    if (m_arbiter) {delete m_arbiter; m_arbiter = 0;}
	if (m_uart)   {delete m_uart;m_uart=0;}
  }

}; // end class test

#endif
