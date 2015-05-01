/*
The starting state of the model will wait for an event on the road sensor. When this
occurs the NS (North-South) lights will change to yellow, and the model will wait
for the yellow to red delay. After the delay the NS lights are changed to red and the
EW (East-West) lights are changed to green. The model will now wait for the green
to yellow delay to allow the cars to have time to cross the highway. After this delay
is complete the EW lights are changed to yellow and finally to red. The module
waits one more long delay after the highway light goes back to green so that
another car will not trip the sensor immediately.
*/

#include "traff.h"
void traff::control_lights() {
  NSred = false;
  NSyellow = false;
  NSgreen = true;
  EWred = true;
  EWyellow = false;
  EWgreen = false;
  while (true) {
    while (roadsensor == false)
      wait();
    NSgreen = false; // road sensor triggered
    NSyellow = true; // set NS to yellow
    NSred = false;
    for (i=0; i<5; i++)
      wait();
    NSgreen = false; // yellow interval over
    NSyellow = false; // set NS to red
    NSred = true; // set EW to green
    EWgreen = true;
    EWyellow = false;
    EWred = false;
    for (i= 0; i<50; i++)
      wait();
    NSgreen = false; // times up for EW green
    NSyellow = false; // set EW to yellow
    NSred = true;
    EWgreen = false;
    EWyellow = true;
    EWred = false;
    for (i=0; i<5; i++) // times up for EW yellow
      wait();
    NSgreen = true; // set EW to red
    NSyellow = false; // set NS to green
    NSred = false;
    EWgreen = false;
    EWyellow = false;
    EWred = true;
    for (i=0; i<50; i++) // wait one more long
      wait(); // interval before allowing a sensor again
  }
}
