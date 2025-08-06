#include "global.h"

int32_t TIMER0_Init(void) {
  TCCR0A = 0x02;
  TCCR0B = 0x03;
  OCR0A = 249;
  TIFR0 = 0x07;
  TIMSK0 = 0x02;
  return TIMER0_SUCCESS;
}

ISR(TIMER0_COMPA_vect) {
  SYS_TICK++;
}