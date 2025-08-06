#ifndef __TIMER0_H__
#define __TIMER0_H__

#ifdef __cplusplus
extern "C" {
#endif

#define TIMER0_ERROR_BASE         0x00003000
#define TIMER0_SUCCESS            0
#define TIMER0_ERROR_RANGE        (TIMER0_ERROR_BASE + 1) //0x00003001

extern int32_t TIMER0_Init(void);

#ifdef __cplusplus
}
#endif

#endif