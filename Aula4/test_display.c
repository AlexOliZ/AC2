#include <detpic32.h>
#include "send2display.c"
#include "delay.c"

int main(void){
    unsigned int counter = 0;
    unsigned int i = 0;
    //TRISB = TRISB & 0x00FF;

    while(1){
        i=0;
        do{
            delay(10);
            send2display(counter);     
        }while(++i<20);  
        counter++;     
    }
    return 0;
}