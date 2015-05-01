#include "detector.h"

// delta cycle delay
void detector::prc_detect() {
  one = data;
  two = one;
  three = two;
}

void detector::prc_output() {
  seq_detected = one & !two & three;
}

