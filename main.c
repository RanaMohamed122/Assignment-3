// Systick & Timer0 Interrupts by Sherif Hammad December 2018
// Make Timer0 Interrupt priority 4 which is lower than Systick
// Timer0 Period Always : 32 Ticks and Delay call
// Systick 16000 Ticks = 1ms
// Rule: Higher priority interrupt preempts lower priority one


#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

void Timer0A_Init(void);
void SysTick_Init(void);
void delayMs(int n);

int
main(void) {

    SysTick_Init();
    Timer0A_Init();  
    SysTickEnable();      
    TimerEnable(TIMER0_BASE, TIMER_A);
    
    while (1)
    {
         SysCtlSleep();
    }
}
void SysTick_Handler(void){
}

void Timer0AIntHandler(void){
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    delayMs(2);
}


void SysTick_Init(void){
  
    SysTickPeriodSet(16000);
    SysTickIntRegister(SysTick_Handler);
    SysTickIntEnable();
    IntMasterEnable();   
    //SysTickEnable();
    
}

void Timer0A_Init(void){ 
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));
   
  TimerDisable(TIMER0_BASE, TIMER_A);  
  TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
  TimerLoadSet(TIMER0_BASE, TIMER_A, 32);
  TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0AIntHandler);  
  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); 
  TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  IntPrioritySet(INT_TIMER0A, 0x80);
  IntEnable(INT_TIMER0A);

    

}

/* delay n milliseconds (16 MHz CPU clock) */
void
delayMs(int n)
{
    int32_t i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 3180; j++)
            {}  /* do nothing for 1 ms */
}
