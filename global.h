#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#define LED_DEBUG_DDR DDRB
#define LED_DEBUG_PORT  PORTB

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#include "sys.h"
#include "timer0.h"
#include "gpio.h"
#include "usart.h"

#define LED_DEBUG_PIN   13
#define LED_GREEN_PIN    12
#define SW1_PIN         7

#endif