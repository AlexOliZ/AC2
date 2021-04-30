#include <detpic32.h>
#include "delay.c"

int main(void){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    TRISB = (TRISB & 0x00FF);

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    while(1){
        char value = PORTB & 0x000F;
        
        // display esquerda
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x00FF) | (display7Scodes[value & 0x000F] << 8);
        
        delay(8);
        
        // display direita
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x00FF) | (display7Scodes[value >> 4] << 8);
        

        delay(8);
    }
    return 0;
}