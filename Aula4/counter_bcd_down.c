#include <detpic32.h>
// counter em bcd de 99 a 0

void delay(unsigned int ms){
    for(;ms>0;ms--){
        resetCoreTimer();
        while(readCoreTimer()<20000);
    }
}

unsigned int to_bcd(unsigned int value){
    return ((value / 10) << 4) + (value % 10);
}

void display_bcd(unsigned int value){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char display = 0;

    if(display==0){
        LATB = (LATB & 0x80FF) | (display7Scodes[value&0x0F] << 8);
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
    }else{
        LATB = (LATB & 0x80FF) | (display7Scodes[value>>4] << 8);
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
    }

    display = !display;
}

int main(void){
    TRISB = TRISB & 0x80FF;
    TRISD = TRISD & 0xFF9F;
    unsigned int counter = 99;
    unsigned int i = 0;
    while(1){
        
        while(i++<50){
            display_bcd(to_bcd(counter));
            delay(10);
        }
        i=0;
        if(counter==0)
            counter = 99;
        counter -= 1;
    }
    return 0;
}