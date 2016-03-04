/* 
 * File:   main1638.c
 * Author: Papai
 *
 * Created on 5 de Janeiro de 2016, 05:56
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "tm1638.h"
#define _XTAL_FREQ 20000000

/*
 * 
 */

void main(void) {
  #pragma config IESO = OFF
  #pragma config PLLDIV = 5
  #pragma config CPUDIV = OSC1_PLL2
  #pragma config USBDIV = 2
  #pragma config FOSC = HS
  #pragma config WDT = OFF   
  #pragma config MCLRE = ON 
  #pragma config LVP = OFF  
   
  TRISD = 0x00;
  TRISC = 0x00;   

  T1CONbits.T1CKPS1 = 1;   // 1/1 prescaler
  T1CONbits.T1CKPS0 = 1;

  T1CONbits.TMR1CS = 0; //   // Use Internal Clock
  
  T1CONbits.T1RUN = 0;
  TMR1H   = 10       ; // 
  TMR1L   = 20       ; // 
    
  RCONbits.IPEN = 1;              // Enable interrupt system priority feature
  IPR1bits.TMR1IP = 1;            // Timer 1 -> High priority interrupt group
  
  PIE1bits.TMR1IE = 1; // Timer1 overflow interrupt
  
  // Enable Timer 1
  T1CONbits.TMR1ON = 1;

  INTCONbits.PEIE = 0; // Enable Perpherial Interrupt
  //INTCONbits.GIE = 1; // Enable Global Interrupt
  INTCONbits.GIEH = 0;            // Enable high priority interrupts
  INTCONbits.GIEL = 0;            // Enable low priority interrupts
//     DisplayLongNumber(88880000);
     WriteCmd(0x8F);
     WriteCmd(0x40);
//  for ( long k = 0 ; k < 100; k++) {  __delay_ms(10); };
  DisplayString("FErnANDO");
  for ( long k = 0 ; k < 1000; k++) {  __delay_ms(10); };
  DisplayString(" CUSAO  " );
 for ( long k = 0 ; k < 1000; k++) {  __delay_ms(10); };
  while(1)
   {
   
   for (signed long i = 0; i < 99999999 ; i++) {
     DisplayLongNumber(i);
     LATCbits.LATC7 ^= 1;
     LATCbits.LATC7 ^= 1;
     WriteCmd(0x8F);
     WriteCmd(0x40);
     //     LedRefresh();     
//     _delay(100000);
   };
  };
   
    return;
};
    

