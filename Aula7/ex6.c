#include <detpic32.h>

volatile unsigned char voltage = 0;

unsigned char toBcd(unsigned char value)
{
    return ((value/10)<<4) + (value%10);
}

void send2display(unsigned char value)
{
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    static char displayFlag = 0;

    int digit_low = value & 0x0F;
    int digit_high = value >> 4;

    if(displayFlag == 0)
    {
        LATB = (LATB & 0x00FF) | (display7Scodes[digit_low] << 8);
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
    }else{
        LATB = (LATB & 0x00FF) | (display7Scodes[digit_high] << 8);
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
    }

    displayFlag = !displayFlag;
}

void _int_(4) isr_t1(void)
{
    /* start conversion */
    AD1CON1bits.ASAM = 1;
    IFS0bits.T1IF = 0;
}

void _int_(12) isr_t3(void)
{
    /* display voltage */
    send2display(voltage);
    IFS0bits.T3IF = 0;
}

void _int_(27) isr_ad1(void)
{
    int port_read = PORTB & 0x03;
    if(port_read != 1)
    {
        int sum = 0;
        int *p = (int*)(&ADC1BUF0);
        for(;p<=(int*)(&ADC1BUFF);p+=4)
        {
            sum += *p;
        }
        double average = (double) sum/8.0;
        voltage = (char)((average*33)/1023);
        voltage = toBcd(voltage & 0xFF);
        IFS1bits.AD1IF = 0;
    }
}

int main(void)
{
    /* TRIS */
    TRISB = TRISB & 0x80FF;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;

    /*  Config ADC */
    TRISBbits.TRISB4 = 1;       // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0;       // RBx configured as analog input (AN4)
    AD1CON1bits.SSRC = 7;       // Conversion trigger selection bits: in this
                                // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1;    // Stop conversions when the 1st A/D converter
                                // interrupt is generated. At the same time,
                                // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 8-1;    // Interrupt is generated after XX samples
                                // (replace XX by the desired number of
                                // consecutive samples)
    AD1CHSbits.CH0SA = 4;       // replace x by the desired input
                                // analog channel (0 to 15)
    AD1CON1bits.ON = 1;         // Enable A/D converter
                                // This must the last command of the A/D
                                // configuration sequence
    IPC6bits.AD1IP = 2;         //priority 2
    IEC1bits.AD1IE = 1;         //interrupts enabled
    IFS1bits.AD1IF = 0;         //reset interrupts flag

    /*  Config T1 */
    T1CONbits.TCKPS = 3;    // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR1 = 19530;            // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR1 = 0;               // Reset timer T1 count register
    
    IPC1bits.T1IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T1IE = 1; // Enable timer T1 interrupts
    IFS0bits.T1IF = 0; // Reset timer T1 interrupt flag 
    
    T1CONbits.TON = 1;      // Enable timer T1 (must be the last command of the


    /*  Config T3 */
    T3CONbits.TCKPS = 2;    // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR3 = 49999;            // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0;               // Reset timer T3 count register

    IPC3bits.T3IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1; // Enable timer T3 interrupts
    IFS0bits.T3IF = 0; // Reset timer T3 interrupt flag 

    T3CONbits.TON = 1;      // Enable timer T3 (must be the last command of the


    EnableInterrupts();
    while(1);
    return 0;
}