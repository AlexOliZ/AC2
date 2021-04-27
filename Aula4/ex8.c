#include <detpic32.h>


int main(void){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    
    // configure RB0 to RB3 as inputs    
    TRISB = (TRISB & 0x000F);

    // configure RB8 to RB14 and RD5 to RD6 as outputs
    

    // Select display low 

    while(1){
        // read dip-switch             
        // convert to 7 segments code             
        // send to display 


    }

    return 1;
}