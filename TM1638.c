#include <xc.h>
#include <stdio.h>

#define DO  LATDbits.LATD1
#define DI  PORTDbits.RD1

#define CLK LATDbits.LATD0
#define STB LATDbits.LATD2
#define	DatCmd	0X40
#define	LedCmd	0x80
#define	AdrCmd	0XC0

const char FontNumber[] = {
  0b00111111, // 0
  0b00000110, // 1  
  0b01011011, // 2
  0b01001111, // 3  
  0b01100110, // 4  
  0b01101101, // 5  
  0b01111101, // 6  
  0b00000111, // 7  
  0b01111111, // 8  
  0b01101111, // 9  
  0b01110111, // A
  0b01111100, // B
  0b00111001, // C
  0b01011110, // D
  0b01111001, // E
  0b01110001  // F
};

const char FontChar[] = {
  0b00000000, // (32)  <space>
  0b10000110, // (33)	!
  0b00100010, // (34)	"
  0b01111110, // (35)	#
  0b01101101, // (36)	$
  0b00000000, // (37)	%
  0b00000000, // (38)	&
  0b00000010, // (39)	'
  0b00110000, // (40)	(
  0b00000110, // (41)	)
  0b01100011, // (42)	*
  0b00000000, // (43)	+
  0b00000100, // (44)	,
  0b01000000, // (45)	-
  0b10000000, // (46)	.
  0b01010010, // (47)	/
  0b00111111, // (48)	0
  0b00000110, // (49)	1
  0b01011011, // (50)	2
  0b01001111, // (51)	3
  0b01100110, // (52)	4
  0b01101101, // (53)	5
  0b01111101, // (54)	6
  0b00100111, // (55)	7
  0b01111111, // (56)	8
  0b01101111, // (57)	9
  0b00000000, // (58)	:
  0b00000000, // (59)	;
  0b00000000, // (60)	<
  0b01001000, // (61)	=
  0b00000000, // (62)	>
  0b01010011, // (63)	?
  0b01011111, // (64)	@
  0b01110111, // (65)	A
  0b01111111, // (66)	B
  0b00111001, // (67)	C
  0b00111111, // (68)	D
  0b01111001, // (69)	E
  0b01110001, // (70)	F
  0b00111101, // (71)	G
  0b01110110, // (72)	H
  0b00000110, // (73)	I
  0b00011111, // (74)	J
  0b01101001, // (75)	K
  0b00111000, // (76)	L
  0b00010101, // (77)	M
  0b00110111, // (78)	N
  0b00111111, // (79)	O
  0b01110011, // (80)	P
  0b01100111, // (81)	Q
  0b00110001, // (82)	R
  0b01101101, // (83)	S
  0b01111000, // (84)	T
  0b00111110, // (85)	U
  0b00101010, // (86)	V
  0b00011101, // (87)	W
  0b01110110, // (88)	X
  0b01101110, // (89)	Y
  0b01011011, // (90)	Z
  0b00111001, // (91)	[
  0b01100100, // (92)	\ (this can't be the last char on a line, even in comment or it'll concat)
  0b00001111, // (93)	]
  0b00000000, // (94)	^
  0b00001000, // (95)	_
  0b00100000, // (96)	`
  0b01011111, // (97)	a
  0b01111100, // (98)	b
  0b01011000, // (99)	c
  0b01011110, // (100)	d
  0b01111011, // (101)	e
  0b00110001, // (102)	f
  0b01101111, // (103)	g
  0b01110100, // (104)	h
  0b00000100, // (105)	i
  0b00001110, // (106)	j
  0b01110101, // (107)	k
  0b00110000, // (108)	l
  0b01010101, // (109)	m
  0b01010100, // (110)	n
  0b01011100, // (111)	o
  0b01110011, // (112)	p
  0b01100111, // (113)	q
  0b01010000, // (114)	r
  0b01101101, // (115)	s
  0b01111000, // (116)	t
  0b00011100, // (117)	u
  0b00101010, // (118)	v
  0b00011101, // (119)	w
  0b01110110, // (120)	x
  0b01101110, // (121)	y
  0b01000111, // (122)	z
  0b01000110, // (123)	{
  0b00000110, // (124)	|
  0b01110000, // (125)	}
  0b00000001, // (126)	~
};


char DisplayBuffer[8] = {0,0,0,0,0,0,0,0};
char DecPointBuffer1 = {0b00000000};
char LedBuffer1 = {0b00000000};
char LedBuffer2 = {0b00000000};

//char LedBuffer{3] = {0,0,0};

void Write1638( unsigned char Data )	
{
	unsigned char i;
	for( i=0 ; i<8 ; i++ )	{
        DO = (Data & 0X01);
		CLK = 0;
		Data >>= 1;
        _delay(2);
		CLK = 1;
	}
    _delay(20);
}

unsigned char Read1638(void) {
	unsigned char i;
	unsigned char temp=0;
	DO = 1;	
	for( i=0 ; i<8 ; i++ ) 	{
		temp >>= 1;
		CLK = 0;
		if(DI)
			temp |= 0x80;
		CLK = 1;
	}
	return temp;
}

void WriteCmd(unsigned char cmd) {
	STB = 0;
	Write1638(cmd);
	STB = 1;
}

void WriteData(unsigned char Adress,unsigned char Data) {
	WriteCmd(0x44);
	STB = 0;
	Write1638( 0xc0 | Adress );
	Write1638( Data );
	STB = 1;
}

void LedRefresh (void)
{ 
    CLK = 1;
	WriteCmd(0x40);
    STB = 0;
    Write1638( 0xC0 );
    Write1638( FontNumber[DisplayBuffer[0]] );
    Write1638( 0b11111100 );
    Write1638( FontNumber[DisplayBuffer[1]] );
    Write1638( 0b11111111 );
    Write1638( FontNumber[DisplayBuffer[2]] );
    Write1638( 0b11111100 );
    Write1638( FontNumber[DisplayBuffer[3]] );
    Write1638( 0b11111111 );
    Write1638( FontNumber[DisplayBuffer[4]]  );
    Write1638( 0b11111100 );
    Write1638( FontNumber[DisplayBuffer[5]] );
    Write1638( 0b11111111 );
    Write1638( FontNumber[DisplayBuffer[6]] );
    Write1638( 0b11111100 );
    Write1638( FontNumber[DisplayBuffer[7]] );
    Write1638( 0b11111111 );
	STB = 1;
    CLK = 1;
}

void Init1638(void) {
    STB = 1;
    CLK = 1;
    _delay(4000);
	WriteCmd( 0x40 );
    WriteDisplayBuffer();
    _delay(400);       
}

void WriteDigit( char number,char pos )
{
	WriteCmd(0x44);
	STB = 0;
	Write1638( 0xc0 | pos );
	Write1638( FontNumber[ 0X0f & number ]);
	STB = 1;
    WriteCmd( 0x89 );        
}

void DisplayLongNumber(signed long number)
{
  unsigned char  und,dec,cnt,mil,decmil,decmil,cntmil,mlh,decmlh;
  signed long tmp;
  und     = number%10  ;
  tmp     = number/10  ;
  dec     = tmp%10     ;
  tmp     = tmp/10     ;
  cnt     = tmp%10     ;
  tmp     = tmp/10     ;
  mil     = tmp%10     ;
  tmp     = tmp/10     ;
  decmil  = tmp%10     ; 
  tmp     = tmp/10     ;
  cntmil  = tmp%10     ; 
  tmp     = tmp/10     ;
  mlh     = tmp%10     ; 
  tmp     = tmp/10     ;
  decmlh  = tmp%10     ; 
  CLK = 1;
    WriteCmd(0x40);
    STB = 0;
    Write1638( 0xC0 );
    Write1638( FontChar[decmlh+16] );
    Write1638( 0b11111100 );
    Write1638( FontChar[mlh+16] );
    Write1638( 0b11111111 );
    Write1638( FontChar[cntmil+16] );
    Write1638( 0b11111100 );
    Write1638( FontChar[decmil+16] );
    Write1638( 0b11111111 );
    Write1638( FontChar[mil+16]  );
    Write1638( 0b11111100 );
    Write1638( FontChar[cnt+16] );
    Write1638( 0b11111111 );
    Write1638( FontChar[dec+16] );
    Write1638( 0b11111100 );
    Write1638( FontChar[und+16] );
    Write1638( 0b11111111 );
	STB = 1;
    CLK = 1;
}

void DisplayString( const char *msg)
{
      CLK = 1;
	WriteCmd(0x40);
    STB = 0;
    Write1638( 0xC0 );
    Write1638( FontChar[msg[0]-32] );
    Write1638( 0b11111100 );
    Write1638( FontChar[msg[1]-32] );
    Write1638( 0b11111111 );
    Write1638( FontChar[msg[2]-32] );
    Write1638( 0b11111100 );
    Write1638( FontChar[msg[3]-32] );
    Write1638( 0b11111111 );
    Write1638( FontChar[msg[4]-32]  );
    Write1638( 0b11111100 );
    Write1638( FontChar[msg[5]-32] );
    Write1638( 0b11111111 );
    Write1638( FontChar[msg[6]-32] );
    Write1638( 0b11111100 );
    Write1638( FontChar[msg[7]-32] );
    Write1638( 0b11111111 );
	STB = 1;
    CLK = 1;
}
