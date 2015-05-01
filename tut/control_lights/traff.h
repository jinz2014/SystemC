nclude "systemc.h"
SC_MODULE(traff) {
   //input ports
   sc_in<bool> roadsensor;
   sc_in<bool> clock;
   // output ports
   sc_out<bool> NSred;
   sc_out<bool> NSyellow;
   sc_out<bool> NSgreen;
   sc_out<bool> EWred;
   sc_out<bool> EWyellow;
   sc_out<bool> EWgreen;
   void control_lights();
   int i;

   // Constructor
   SC_CTOR(traff) {
     SC_THREAD(control_lights); // Thread Process
     sensitive << roadsensor;
     sensitive_pos << clock;
   }
};
