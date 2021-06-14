#include <detpic32.h>
#include "../Utils/utils.h"

int main(void){
    T3CONbits.TCKPS = 7;    //Kprescaler = 256
    PR3 = 39062;            //Fout = 2Hz (PBLCK / (256*(39062+1))
    TMR3 = 0;               //Reset timer T3 count register
    T3CONbits.TON = 1; 
    
    //configure Timer T3 interrupts
    IPC3bits.T3IP = 2;          //set priority
    IEC0bits.T3IE = 1;          //enable interruputs
    IFS0bits.T3IF = 0;          // reset interrupts flag
    EnableInterrupts();
    
    while(1);
}

void _int_(12) isr_t3(void)
{
    putChar('.');
    IFS0bits.T3IF = 0;
}