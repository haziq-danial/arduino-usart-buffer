#include "global.h"

int32_t GPIO_Init(void) {
  DDRD = 0x00;
  DDRB = 0x00;
  PORTD = 0x00;
  PORTB = 0x00;
  return GPIO_SUCCESS;
}

int32_t GPIO_Mode(uint8_t pin, uint8_t direction) {
  if (pin > GPIO_MAX) return GPIO_ERROR_RANGE;
  if (direction > GPIO_OUTPUT) return GPIO_ERROR_RANGE;


  if (direction == GPIO_OUTPUT) {     //output
    if (pin < 8) DDRD |= (1 << pin);  //port D 10 to 7
    else DDRB |= (1 << (pin & 7));
  } else {                             //input
    if (pin < 8) DDRD |= ~(1 << pin);  //PORTD 0 to 7
    else DDRB |= ~(1 << (pin & 7));    //PORTB (8 to 13,becomes 0 to 5)
  }
  return GPIO_SUCCESS;
}

int32_t GPIO_Write(uint8_t pin, uint8_t state) {
  if (pin > GPIO_MAX) return GPIO_ERROR_RANGE;
  if (state > GPIO_HIGH) return GPIO_ERROR_VALUE;

  if (state == GPIO_HIGH) {
    if (pin < 8) PORTD |= (1 << pin);
    else (PORTB |= (1 << (pin & 7)));
  } else {
    if (pin < 8) PORTD &= ~(1 << pin);
    else (PORTB &= ~(1 << (pin & 7)));
  }

  return GPIO_SUCCESS;
}

int32_t GPIO_Read(uint8_t pin, uint8_t* value) {
  if (pin > GPIO_MAX) return GPIO_ERROR_RANGE;

  if (pin < 8) *value = PORTD & (1 << pin);  // PIND (0 to 7)
  else *value = PORTB & (1 << (pin & 7));    // PINB (8 to 13, becomes 0 to 5)

  if (*value > 0) *value = GPIO_HIGH;
  return GPIO_SUCCESS;
}
