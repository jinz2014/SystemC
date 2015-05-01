#include "mux.h"

void mux2 :: mux() {
  switch ( s.read() ) {
    case 0: o=a;
    case 1: o=b;
  }
}
