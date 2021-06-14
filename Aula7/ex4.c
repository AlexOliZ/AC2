#include <detpic32.h>

void _int_(4) isr_t1(void){
    printInt10(1);
    IFS0bits.T1IF = 0;          //reset T1IF flag
}

void _int_(12) isr_t3(void){
    printInt10(3);
    IFS0bits.T3IF = 0;          //reset T1IF flag
}

int main(void){

    /* Config T1 */
    T1CONbits.TCKPS = 3;    //Kprescaler = 256  FoutPrescaler = 78125Hz;
    PR1 = 39062;            //Fout = 2Hz = (PBLCK/(39062+1)*256)
    TMR1 = 0;
    T1CONbits.TON = 1;
    /* T1 interrupts */
    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;

    /* Config T3 */
    T3CONbits.TCKPS = 5;    //Kprescaler = 32  FoutPrescaler = 62500Hz;
    PR3 = 62499;            //Fout = 10Hz = (PBLCK/(62499+1)*32)
    TMR3 = 0;
    T3CONbits.TON = 1;
    /* T3 interrupts */
    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0;

    EnableInterrupts();
    while(1);
}