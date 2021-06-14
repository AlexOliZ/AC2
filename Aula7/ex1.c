#include <detpic32.h>
#include "../Utils/utils.h"

int main(void){
    // para configurar timers
    T3CONbits.TCKPS = 7;    //Kprescaler = 256
    PR3 = 39062;            //Fout = 2Hz (PBLCK / (256*(39062+1))
    TMR3 = 0;               //Reset timer T3 count register
    T3CONbits.TON = 1; 

    while(1){
        while(IFS0bits.T3IF==0);
        IFS0bits.T3IF = 0;
        putChar('.');
    }

    return 0;
}