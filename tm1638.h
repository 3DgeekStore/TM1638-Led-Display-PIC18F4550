/* 
 * File:   tm1638.h
 * Author: Papai
 *
 * Created on 5 de Janeiro de 2016, 05:58
 */

#ifndef TM1638_H
#define	TM1638_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* TM1638_H */

void Write1638( unsigned char Data );
unsigned char Read1638(void);
void WriteCmd(unsigned char cmd);
void WriteData(unsigned char Adress,unsigned char Data) ;
void LedRefresh (void);
void Init1638(void);
void WriteDigit( char number,char pos);
void DisplayLongNumber(signed long number);
void DisplayString( const char msg[]);


