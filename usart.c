#include "global.h"

uint8_t USART_TX_BUF[USART_TX_BUF_SIZE];
uint8_t USART_TX_BUF_WR, USART_TX_BUF_RD, USART_TX_BYTES;

uint8_t USART_RX_BUF[USART_RX_BUF_SIZE];
uint8_t USART_RX_BUF_WR, USART_RX_BUF_RD, USART_RX_BYTES;

int32_t USART_Init(void) {
  UBRR0H = (USART_BAUD_PRESCALE >> 8);  //set baudrate
  UBRR0L = USART_BAUD_PRESCALE;
  UCSR0C |= 0x06;  //8-bit data
  UCSR0B |= 0x18;  //enable tx & rx

  return USART_SUCCESS;
}


int32_t USART_Write(uint8_t byte) {
  while ((UCSR0A & 0x20) == 0);  //wait until USART ready
  UDR0 = byte;  //transmit byte
  return USART_SUCCESS;
}

int32_t USART_Write_String(char *str, uint8_t size) {
  uint8_t i;
  for(i = 0; i < size; i++) {
    if(USART_TX_BYTES >= USART_TX_BUF_WR) {
      while(USART_TX_BYTES >= USART_TX_BUF_SIZE) USART_Process();
    }
    USART_TX_BUF[USART_TX_BUF_WR] = *str;
    str++;
    USART_TX_BUF_WR = (USART_TX_BUF_WR + 1) & (USART_TX_BUF_SIZE - 1);
    USART_TX_BYTES++;
  }

  return USART_SUCCESS;
}

int32_t USART_Read(uint8_t *count, uint8_t *byte) {
  if((UCSR0A & 0X80) != 0X80) *count = 0;
  else {
    *byte = UDR0;
    *count = 1;
  }
  return USART_SUCCESS;  //receive byte
}

int32_t USART_Process(void) {
  if((UCSR0A & 0x20) && (USART_TX_BYTES > 0)) {
    UDR0 = USART_TX_BUF[USART_TX_BUF_RD]; // write to USART HW to transmit
    USART_TX_BUF_RD = (USART_TX_BUF_RD + 1) & (USART_TX_BUF_SIZE - 1);
    USART_TX_BYTES--;
  }

  if(((UCSR0A & 0x80) == 0x80) && (USART_RX_BYTES < USART_RX_BUF_SIZE)) {
    USART_RX_BUF[USART_RX_BUF_WR] = UDR0; // read buffer
    USART_RX_BUF_WR = (USART_RX_BUF_WR + 1) & (USART_RX_BUF_SIZE - 1);
    USART_RX_BYTES--;
  }
  return USART_SUCCESS;
}

