#include <detpic32.h>
// ler valores do switch e enviar para o display em BCD

void delay(unsigned int ms){
    for(;ms>0;ms--){
        resetCoreTimer();
        while(readCoreTimer()<20000);
    }
}

unsigned int toBcd(unsigned int value){
    return ((value / 10) << 4) + (value % 10);
}

void send2display(unsigned int value){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char display = 0;

    if(display==0){
        LATB = (LATB & 0x80FF) | (display7Scodes[value&0x0F]<< 8);
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
    }else{
        LATB = (LATB & 0x80FF) | (display7Scodes[value>>4]<< 8);
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
    }

    display = !display;
}

int main(void){
    TRISB = TRISB | 0x000F;
    TRISB = TRISB & 0x80FF;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD5 = 0;
    unsigned int val=0;
    while(1){
        val = PORTB & 0x000F;
        send2display(toBcd(val));
        delay(10);
    }

    return 0;
}