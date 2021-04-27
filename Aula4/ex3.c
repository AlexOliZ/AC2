#include <detpic32.h>
#include "delay.c"
#include "charUtils.c"

int main(void){
    // configurar D5,D6 e D8 a D15 como saidas
    char c;
    
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISB = TRISB & 0x00FF;
    
    // ativar LATD5 desativado e LATD6 ativado
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;

    while(1){
        while(1){
            c = toLowerCase(getChar());
            if((c >= 'a' && c <= 'g') || (c == '.')){
                putChar(c);
                break;
            }
        }
        delay(250);
        switch(c){
            case 'a':
                LATBbits.LATB8 = 1;
                break;
            case 'b':
                LATBbits.LATB9 = 1;
                break;

            case 'c':
                LATBbits.LATB10 = 1;
                break;
            case 'd':
                LATBbits.LATB11 = 1;
                break;
            case 'e':
                LATBbits.LATB12 = 1;
                break;
            case 'f':
                LATBbits.LATB13 = 1;
                break;
            case 'g':
                LATBbits.LATB14 = 1;
                break;
            case '.':
                LATBbits.LATB15 = 1;
                break;
        }

    }
}