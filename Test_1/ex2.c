#include <detpic32.h>

void delay(int ms){

    for(;ms>0;ms--){

        resetCoreTimer();
        while(readCoreTimer()<20000);
    }
}

void send2displays(unsigned char value){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0;

    TRISB = (TRISB & 0x00FF);

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    int digit_low = value & 0x0F;
    int digit_high = value >> 4;

    if(displayFlag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x00FF) | (display7Scodes[digit_low] << 8);
        
    }else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x00FF) | (display7Scodes[digit_high] << 8);
        
    }

    displayFlag = !displayFlag;
}

int main(void){

    TRISB = TRISB & 0x00FF;
    TRISD = TRISD & 0xFF9F;

    LATB = LATB & 0x00FF;
    
    int c;
    int i = 0;
    int key = 0;
    while(1){
        key = inkey();
        if(key != 0){
            c = key&0x0F; 
        }
        if(c>=0 && c<=3){
            send2displays(c);
        }else if(c>0){
            while (i++<100){
                delay(10);
                send2displays(255);
            }   
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 0;
            i = 0;
            c = -1;
        }
    }
    return 0;
}