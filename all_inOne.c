#include <detpic32.h>

// se o switch tiver a 0 -> display counter crescente 
// se o switch tiver a 1 -> display counter decrescente
// se o switch tiver a 2 -> display counter BCD
// else ex3 -> Test_1

void delay(unsigned int ms){
    for(;ms>0;ms--){
        resetCoreTimer();
        while(readCoreTimer()<20000);
    }
}

void send2display(unsigned int value){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0;
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 0;

    if(displayFlag == 0){
        LATB = (LATB & 0x80FF) | (display7Scodes[value&0x0F]<<8);
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        
    }else{  
        LATB = (LATB & 0x80FF) | (display7Scodes[value>>4]<<8);
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;        
    }
    displayFlag = !displayFlag;
}   

unsigned int toBCD(unsigned int value){
    return ((value / 10) << 4) + (value % 10);
}
// durante 4 seg
void display_ADC(void){
    int N = 4;
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
    AD1CON2bits.SMPI = N-1;       // Interrupt is generated after XX samples 
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
    unsigned int soma=0;
    unsigned int i=0;
    int counter = 0x00FF;

    while(counter!=0){
        AD1CON1bits.ASAM = 1;
        soma = 0;
        while( IFS1bits.AD1IF == 0 );

        int* p = (int*)(&ADC1BUF0);
        for(i=0;i<N;i++){
            soma += p[i*4];
        }
        value = soma/N;
        freq = 1+value/256;
        ms = 1/freq;
        ms+=1;
        send2display(counter);
        delay(ms*10);
        printInt(ms,10);
        counter-=1;
    }
}
// até 50
void counter_up(unsigned int value){
    unsigned int i=0;
    unsigned int counter = 0;
    while(counter<=value){
        // 4hz
        while(i++<25){
            send2display(counter);
            delay(10);
        }
        i=0;
        counter+=1;
    }

}

// até 0
void counter_down(unsigned int value){
    unsigned int i=0;
    while(value>0){
        // 4hz
        while(i++<25){
            send2display(value);
            delay(10);
        }
        i=0;
        value-=1;
    }
}


int main(void){
    TRISB = (TRISB | 0x000F) & 0x80FF;
    // display valor do switch nos LEDS
    TRISE = TRISE&0xFFF0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    unsigned int value=0;
    unsigned int val=0;

    while(1){
        value = PORTB & 0x000F;
        
        if(value == 1){
            LATE = LATE&0xF1;   
            printInt(value,10);
            counter_up(0x0FF);
        }else if(value == 2){
            LATE = LATE&0xF2;
            printInt(value,10);
            counter_down(0x0FF);   
        }else if(value == 4){
            LATE = LATE&0xF4;
            printInt(value,10);
            val = toBCD(50);
            counter_down(val);    
            counter_up(val);    
        }else if(value == 8){
            LATE = LATE&0xF8;
            printInt(value,10);
            display_ADC();
        }

    }

    return 0;

}