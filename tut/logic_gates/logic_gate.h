#include "systemc.h"
#include "type.h"


SC_MODULE (logic_gate) {
  sc_in<sc_lv<4> > in;
  sc_out<sc_logic> z;

  void prc_and_gate();
  void prc_nand_gate();
  void prc_or_gate();
  void prc_nor_gate();
  void prc_xor_gate();


  SC_HAS_PROCESS(logic_gate);
  logic_gate (sc_module_name name, gate_type gate) : 
    sc_module(name) {
   switch (gate) {
     case AND:
       SC_METHOD(prc_and_gate);
       sensitive << in;
       break;
     case NAND:
       SC_METHOD(prc_nand_gate);
       sensitive << in;
       break;
     case OR:
       SC_METHOD(prc_or_gate);
       sensitive << in;
       break;
     case NOR:
       SC_METHOD(prc_nor_gate);
       sensitive << in;
       break;
     case XOR:
       SC_METHOD(prc_xor_gate);
       sensitive << in;
       break;
    }
  }
};
     
