#include <stdint.h>
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

#define USART_ERROR_BASE                0x00004000
#define USART_SUCCESS                   0
#define USART_ERROR_TX_BUF_FULL         (USART_ERROR_BASE + 1) //0x00004001
#define USART_ERROR_TX_BUF_EMPTY        (USART_ERROR_BASE + 2) //0x00004001

#define USART_BAUDRATE                  9600
#define USART_BAUD_PRESCALE             (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define USART_TX_BUF_SIZE               32
#define USART_RX_BUF_SIZE               32

extern uint8_t USART_TX_BYTES;
extern uint8_t USART_TX_BUF_WR;
extern uint8_t USART_TX_BUF_RD;
extern uint8_t USART_TX_BUF[USART_TX_BUF_SIZE];

extern uint8_t USART_RX_BUF[USART_RX_BUF_SIZE];
extern uint8_t USART_RX_BUF_WR; 
extern uint8_t USART_RX_BUF_RD; 
extern uint8_t USART_RX_BYTES;

extern int32_t USART_Init(void);
extern int32_t USART_Write(uint8_t byte);
extern int32_t USART_Read(uint8_t *count, uint8_t *byte);
extern int32_t USART_Write_String(char *str, uint8_t size);
extern int32_t USART_Process(void);

#ifdef __cplusplus
}
#endif

#endif