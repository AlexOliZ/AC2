#include <detpic32.h>

static int count=0;

void _int_(12) isr_t3(void)
{
    if(count==1){
        putChar('.');
        count-=1;
    }else
        count++;

    IFS0bits.T3IF = 0;
}

int main(void)
{
    // config timer
    T3CONbits.TCKPS = 7;
    PR3 = 39062;
    TMR3 = 0;
    T3CONbits.TON = 1;
    
    // interrupts
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    EnableInterrupts();
    while(1);
}