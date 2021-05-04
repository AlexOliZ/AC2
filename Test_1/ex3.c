#include <detpic32.h>

void delay(unsigned int ms){
    for(;ms>0;ms--){
        RESET_CORE_TIMER();
        while(READ_CORE_TIMER() < 20000)
    }

}

void send2display(unsigned int value){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0;
    TRISB = TRISB && 0x80FF;
    
    if(displayFlag == 0){
        LATB = (LATB & 0x00FF) | (display7Scodes[value&0x0F]<<8); 
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
    }else{
        LATB = (LATB & 0x00FF) | (display7Scodes[value>>4]<<8); 
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
    }

    displayFlag = !displayFlag;
}

int main(void){

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;

    TRISBbits.TRISB4 = 1;       // RBx digital output disconnected 
    AD1PCFGbits.PCFG4 = 0;      // RBx configured as analog input (AN4)
    AD1CON1bits.SSRC = 7;       // Conversion trigger selection bits: in this
                                // mode an internal counter ends sampling and
                                // starts conversion
    
    AD1CON1bits.CLRASAM = 1;    // Stop conversions when the 1st A/D converter
                                // interrupt is generated. At the same time, 
                                // hardware clears the ASAM bit 
    
    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100 ns) 
    AD1CON2bits.SMPI = 0;       // Interrupt is generated after XX samples 
                                // (replace XX by the desired number of
                                // consecutive samples) 
    
    AD1CHSbits.CH0SA = 4;       // replace x by the desired input
                                // analog channel (0 to 15)
    
    AD1CON1bits.ON = 1;         // Enable A/D converter 
                                // This must the last command of the A/D
                                // configuration sequence 
    unsigned int ms=0;
    unsigned int value=0;
    unsigned int freq=0;
    unsigned int counter = 0x00FF;

    while(1){
        counter = counter & 0x00FF;
        send2display(counter);

        AD1CON1bits.ASAM = 1;
        while(IFS1bits.AD1IF == 0);

        value = ADC1BUF0;
        freq = 1+val/256;
        ms = 1/freq;
        
        delay(ms);
        //if(counter == 0)
        //   counter = 0x01FF;
        counter-=1;
    }
    return 0;
}