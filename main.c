/*
 * File:   main.c
 * Author: khing
 *
 * Created on August 16, 2018, 8:39 PM
 */

#pragma config FOSC = HS // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config PWRTE = OFF // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config IESO = ON // Internal/External Switch Over (Internal External Switch Over mode is enabled)
#pragma config FCMEN = ON // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)
#pragma config WRT = OFF // Flash Memory Self-Write Protection (Write protection off)
#pragma config LVP = ON // Low-Voltage Programming Enable (Low-voltage programming enabled)
#pragma config WDTE = OFF // Watchdog Timer Enable (WDT disabled)

#include <xc.h>
#define _XTAL_FREQ 20000000
int Time;
const char SINETABLE[360]=
 {
127,134,140,147,153,160,166,173,
179,185,191,196,202,207,212,217,
221,226,230,234,237,240,243,246,
248,250,251,252,253,254,254,254,
253,252,251,250,248,246,243,240,
237,234,230,226,221,217,212,207,
202,196,191,185,179,173,166,160,
153,147,140,134,127,120,114,107,
101,94,88,81,75,69,64,58,
52,47,42,37,33,28,24,20,
17,14,11,8,6,4,3,2,
1,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,1,2,3,4,
6,8,11,14,17,20,24,28,
33,37,42,47,52,58,64,69,
75,81,88,94,101,107,114,120};
int step[3]={0,120,240};
void setup(void){
    TRISA = 0b11001111;
    TRISB = 0b11001000;
    TRISC = 0b11111000;
    //TRISAbits.TRISA0=1;
    ANSEL = 0b11111011;
    //Setup TMR0 Interrupt.
    TMR0 = 0; //TMR0 initiation
    T0CS = 0; //Choose to work with internal CLK
    T0SE = 0; //React on LowToHigh
    T0IE = 1; //enable TMR0 overflow interrupts
    GIE = 1; //enable Global interrupts
    PSA = 0; //Work with Prescler
    PS0 = 0;
    PS1 = 0;
    PS2 = 0;
    PORTB=0xFF;
}
void main(void) {
    setup();
    
    while (1) {
        //if (T0IF) {
        //    T0IF = 0;
            Time++;
            //PORTB=0xFF;
            if(Time>254){
                Time=0;
                for(int o=0;o<3;o++){
                    //step[o]++;
                    if(++step[o]>360){
                    step[o]=0;
                    }
                }
            //}
                
        }
        if(Time<SINETABLE[step[0]]){
            PORTB=PORTB&0b11111011;
        }else{
            PORTB=PORTB|0b00000100;
        }
        if(Time<SINETABLE[step[1]]){
            PORTB=PORTB&0b11101111;
        }else{
            PORTB=PORTB|0b00010000;
        }
        if(Time<SINETABLE[step[2]]){
            PORTB=PORTB&0b11011111;
        }else{
            PORTB=PORTB|0b00100000;
        }
        
    }
}