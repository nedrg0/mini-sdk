#include <stdint.h>
#include "stm32f103xb.h"


extern uint32_t _sdata, _edata, _sidata;
extern uint32_t _sbss, _ebss;
extern uint32_t _estack;
static volatile uint32_t ticks = 0;


void Reset_Handler(void);
int main(void);

void Default_Handler(void) {while(1);}

void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) ;
void SysTick_Handler(void) ;
void PendSV_Handler(void) __attribute__((weak));


/* Vector table - must be placed at 0x08000000 */
__attribute__((section(".isr_vector")))
uint32_t vector_table[] = {
	(uint32_t)&_estack,
	(uint32_t)&Reset_Handler, 
	(uint32_t)&NMI_Handler,
	(uint32_t)&HardFault_Handler,
	    0,                               /* 4:  MemManage     */
    0,                               /* 5:  BusFault      */
    0,                               /* 6:  UsageFault    */
    0,                               /* 7:  reserved      */
    0,                               /* 8:  reserved      */
    0,                               /* 9:  reserved      */
    0,                               /* 10: reserved      */
    0,                               /* 11: SVCall        */
    0,                               /* 12: DebugMon      */
    0,                               /* 13: reserved      */
    (uint32_t)&PendSV_Handler,                               /* 14: PendSV        */
    (uint32_t)&SysTick_Handler,      /* 15: SysTick       */
};

void HardFault_Handler(void) {
    /* Read the fault status registers */
    volatile uint32_t hfsr = *(volatile uint32_t *)0xE000ED2C;
    volatile uint32_t cfsr = *(volatile uint32_t *)0xE000ED28;
    volatile uint32_t mmfar = *(volatile uint32_t *)0xE000ED34;
    volatile uint32_t bfar  = *(volatile uint32_t *)0xE000ED38;

    (void)hfsr; (void)cfsr; (void)mmfar; (void)bfar;

    while(1);  /* put a breakpoint here */
}
void SysTick_Handler(void) {
	ticks++;

	__disable_irq();
//	OS_sched();
	__enable_irq();

}
void Reset_Handler(void) {
	/* 1. Copy .data from FLASH to SRAM*/
	uint32_t *src = &_sidata;
	uint32_t *dst = &_sdata;
	while (dst < &_edata) {
		*dst++ = *src++;
	}

	/* Zero .bss*/
	dst = &_sbss;
	while (dst < &_ebss) {
		*dst++ = 0;
	}
	// Call main
	main();

	while(1);
}

