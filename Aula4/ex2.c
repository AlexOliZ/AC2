#include <detpic32.h>
#include "delay.c"

int main(void){
    
    //LATCbits.LATC14 = 0;
    //TRISCbits.TRISC14 = 0;
    int counter = 0;
    // reset aos valores dos portos RE0 a RE3
    LATE = (LATE & 0xFFF0);

    // configurar os portos RE0 a RE3 como saida
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE3 = 0;

    while(1){
        delay(125); // a 4hz
        LATE = (LATE & 0xFFF0) | counter;
        counter++;
    }
    return 0;
}