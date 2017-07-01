#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int

sbit sclk=P0^5;
sbit IO=P0^6;
sbit res=P0^7;
sbit ACC0=ACC^0;
sbit ACC7=ACC^7;
sbit key1=P3^3;
sbit key2=P3^4;
sbit key3=P3^5;


uchar time[7];
uchar sec, min, hour, day, month,weak, year,a=0,n=0;
bit k=0;

uchar code bang[32]={0xEF,0xEF,0x2F,0x00,0x6F,0xEF,0xBB,0xAB,0x2B,0x8B,0xA0,0xAB,0x2B,0xAB,0xBB,0xFF,0xFB,0xFC,0xFF,0x00,0xFF,0xFE,0xED,0xEE,0xEB,0xEB,0x00,0xEB,0xEB,0xEE,0xED,0xFF};/*"棒",1*/		 
uchar code yao[32]={0xEF,0xEF,0xEF,0x00,0x6F,0xFF,0x6B,0x9B,0xBB,0xAB,0x1D,0xBD,0x9C,0xA5,0xFF,0xFF,0xFD,0xBD,0x7E,0x80,0xFF,0xFF,0xFD,0x85,0xBD,0xBD,0x80,0xBD,0xBD,0x05,0xFD,0xFF};/*"摇",0*/
uchar code ni[32]={0xFF,0xFF,0x3F,0x0F,0xF1,0x7F,0xBF,0xCF,0xE1,0xEF,0x6F,0xEF,0xEF,0xAF,0xCF,0xFF,0xFD,0xFE,0xFF,0x00,0xFF,0xDF,0xE7,0xF9,0x7F,0xFF,0x00,0xFF,0xFD,0xF3,0xCF,0xFF};
uchar code xiao[32]={0xBF,0xDF,0x67,0x71,0x67,0x57,0x77,0x57,0xAF,0xB1,0xB7,0xA7,0xD7,0xF7,0xF7,0xFF,0xFB,0xFB,0x7B,0x7B,0xBB,0xDB,0xEB,0xF0,0xEB,0xDB,0xBB,0x7B,0x7B,0xFB,0xFB,0xFF};
//uchar code qi2[32]={0x7F,0x6F,0x6F,0x6F,0x01,0x6F,0x6F,0xFF,0x77,0x77,0x77,0x77,0x07,0xFF,0xFF,0xFF,0xFF,0x3F,0xC1,0xBF,0x00,0x77,0x77,0x7F,0x60,0x5F,0x5F,0x5F,0x5E,0x47,0x7F,0xFF};
//uchar code lai[32]={0xFF,0xEF,0xEF,0xAF,0x6F,0xEF,0xEF,0x01,0xEF,0xEF,0xEF,0x2F,0xEF,0xEF,0xFF,0xFF,0xBD,0xBD,0xDD,0xDD,0xEC,0xF5,0xF9,0x00,0xF9,0xF5,0xEC,0xDD,0xDD,0xBD,0xBD,0xFF};
uchar code yang[32]={0xDF,0xDF,0x5F,0x01,0xDF,0xFF,0xDF,0xDD,0xD3,0xDF,0x1F,0xDF,0xD7,0xD9,0xDF,0xFF,0xF7,0xF9,0xFE,0x00,0xFE,0xFD,0xF7,0xF6,0xF6,0xF6,0x00,0xF6,0xF6,0xF6,0xF7,0xFF};
uchar code de[32]={0xFF,0x0F,0xE7,0xE9,0xEF,0xEF,0x0F,0x7F,0x9F,0xE1,0xEF,0xEF,0xEF,0x0F,0xFF,0xFF,0xFF,0x00,0xBD,0xBD,0xBD,0xBD,0x00,0xFF,0xFF,0xFE,0x79,0xFF,0x7F,0x80,0xFF,0xFF};
uchar code zi[32]={0x7F,0x7D,0x7D,0x7D,0x7D,0x7D,0x7D,0x1D,0x5D,0x6D,0x75,0x79,0x7D,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBF,0x7F,0x80,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uchar code zhen[32]={0xFF,0xF7,0xF7,0x17,0x57,0x57,0x57,0x41,0x57,0x57,0x57,0x17,0xF7,0xF7,0xFF,0xFF,0xDF,0xDF,0xDF,0x40,0x95,0xD5,0xD5,0xD5,0xD5,0xD5,0x95,0x40,0xDF,0xDF,0xDF,0xFF};
uchar code ke[32]={0xFF,0xFD,0xFD,0x0D,0xED,0xED,0xED,0x0D,0xFD,0xFD,0xFD,0x01,0xFD,0xFD,0xFD,0xFF,0xFF,0xFF,0xFF,0xF0,0xFB,0xFB,0xFB,0xF0,0xFF,0xBF,0x7F,0x80,0xFF,0xFF,0xFF,0xFF};
uchar code ai[32]={0xFF,0x37,0xA7,0x97,0xB7,0xB7,0x27,0x9B,0xBB,0xBB,0x9B,0xA3,0xB9,0xBB,0x3F,0xFF,0xFE,0x7D,0xBD,0xDD,0xED,0xF1,0x64,0x55,0xB5,0xB5,0x55,0x65,0xFD,0xFE,0xFF,0xFF};
uchar code guo[32]={0xFF,0xFF,0xFF,0x01,0x6D,0x6D,0x6D,0x01,0x6D,0x6D,0x6D,0x01,0xFF,0xFF,0xFF,0xFF,0xBB,0xBB,0xDB,0xDA,0xEB,0xF3,0xFB,0x00,0xFB,0xF3,0xEB,0xDA,0xDB,0xBB,0xBB,0xFF}; 
uchar code kong1[8]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uchar code kong2[8]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uchar code kai[32]={0x7F,0x7D,0x7D,0x7D,0x01,0x7D,0x7D,0x7D,0x7D,0x7D,0x01,0x7D,0x7D,0x7D,0x7F,0xFF,0xFF,0x7F,0xBF,0xCF,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0xFF};		
uchar code tian[32]={0xBF,0xBF,0xBD,0xBD,0xBD,0xBD,0xBD,0x01,0xBD,0xBD,0xBD,0xBD,0xBD,0xBF,0xBF,0xFF,0x7F,0x7F,0xBF,0xDF,0xEF,0xF3,0xFC,0xFF,0xFC,0xF3,0xEF,0xDF,0xBF,0x7F,0x7F,0xFF};	
uchar code xin[32]={0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0xFB,0xF7,0xCF,0xFF,0xFF,0xFF,0x7F,0xFF,0xFF,0xFF,0xDF,0xE7,0xF8,0xFF,0xFF,0x80,0x7F,0x7F,0x7F,0x7F,0x7F,0x0F,0xFF,0xFC,0xE3,0xFF}; 
uchar code qing[32]={0xFF,0x3F,0xFF,0x01,0xDF,0x37,0x57,0x57,0x57,0x01,0x57,0x57,0x57,0x77,0x7F,0xFF,0xFD,0xFE,0xFF,0x00,0xFF,0xFF,0x01,0xD5,0xD5,0xD5,0x55,0xD5,0x01,0xFF,0xFF,0xFF};
uchar code hao[32]={0xDF,0xDF,0x1F,0xC1,0xDF,0x1F,0xFF,0xFF,0xFB,0xFB,0x3B,0xDB,0xEB,0xF3,0xFF,0xFF,0x7F,0xBB,0xD4,0xEF,0xD3,0x3C,0xFF,0xFE,0x7E,0xFE,0x00,0xFE,0xFE,0xFE,0xFE,0xFF};
uchar code li[32]={0xFF,0xF7,0x77,0x77,0xB7,0xD7,0xE7,0x01,0xE7,0xD7,0xB7,0x77,0x77,0xF7,0xFF,0xFF,0xEE,0xEE,0xEF,0xEF,0xED,0x6D,0xED,0x0C,0xE5,0xE9,0xED,0xEF,0xEF,0xEE,0xEE,0xFF};
uchar code xuan[32]={0xF7,0xF7,0x07,0xF7,0xF7,0xEF,0x0D,0x63,0x6F,0xDF,0x6F,0x61,0x6F,0x6F,0x6F,0xFF,0xDE,0x9E,0xC0,0xEE,0x6E,0x9F,0xE0,0xBF,0x80,0x7F,0x83,0x7F,0x00,0x77,0x76,0xFF};
uchar code xing[32]={0xFF,0xFF,0xFF,0x41,0xD5,0xD5,0xD5,0x15,0xD5,0xD5,0xD5,0xC1,0xFF,0xFF,0xFF,0xFF,0xFF,0xBB,0xBD,0xB6,0xB6,0xB6,0xB6,0x80,0xB6,0xB6,0xB6,0xB6,0xBE,0xBF,0xFF,0xFF};
uchar code qi[32]={0xFF,0xF7,0x01,0xB7,0xB7,0xB7,0x01,0xF7,0xFF,0x03,0xBB,0xBB,0xBB,0x03,0xFF,0xFF,0xEF,0x6F,0xA0,0xED,0xED,0xCD,0xA0,0x6F,0x9F,0xE0,0xFB,0x7B,0xFB,0x00,0xFF,0xFF};
uchar code nian[32]={0xFF,0xBF,0xCF,0x71,0x77,0x77,0x77,0x77,0x07,0x77,0x77,0x77,0x77,0xF7,0xFF,0xFF,0xF7,0xF7,0xF7,0xF0,0xF7,0xF7,0xF7,0xF7,0x00,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xFF};
uchar code yue[32]={0xFF,0xFF,0xFF,0x01,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0xDD,0x01,0xFF,0xFF,0xFF,0x7F,0xBF,0xCF,0xF0,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD,0xBD,0x7D,0x80,0xFF,0xFF,0xFF};
uchar code xiaonian1[32]={0xFF,0x1F,0xC7,0xF3,0xFB,0x19,0x1D,0xFD,0xFD,0x3D,0x19,0xFB,0xF3,0xE7,0x0F,0x7F,0xFE,0xF0,0xE7,0xCF,0x99,0xB3,0x37,0x27,0x27,0x27,0x33,0xB9,0x9F,0xCF,0xF0,0xFC};
uchar code xiaonian2[32]={0x3F,0xDF,0xFF,0xFD,0x8C,0x86,0xC6,0xFC,0xFD,0x1F,0x8F,0x8B,0xD9,0xF9,0xF1,0xF3,0xF0,0xEF,0xDF,0xBF,0x79,0x73,0x67,0x67,0x67,0x77,0x7B,0x3F,0xBF,0xDF,0xEF,0xF7};
uchar code xiaonian3[32]={0x0F,0xF3,0xF9,0xDD,0xDE,0x96,0x92,0xFE,0xFE,0x9A,0x92,0xD6,0xDD,0xFD,0xFB,0xC7,0xF8,0xE2,0xD6,0x80,0x36,0x00,0x76,0x76,0x00,0x76,0x00,0x36,0x36,0x80,0xC6,0xF0};
uchar code xingq[7][32]={{0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
						 {0xFF,0xFF,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xF7,0xFF,0xFF,0xFF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xFF},
						 {0xFF,0xFB,0x7B,0x7B,0x7B,0x7B,0x7B,0x7B,0x7B,0x7B,0x7B,0x7B,0x7B,0xFB,0xFF,0xFF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xFF},
						 {0xFF,0x01,0xFD,0xFD,0x7D,0x81,0xFD,0xFD,0xFD,0x01,0xFD,0xFD,0xFD,0x01,0xFF,0xFF,0xFF,0xC0,0xEB,0xED,0xEE,0xEF,0xEF,0xEF,0xEF,0xEF,0xEE,0xEE,0xEE,0xC0,0xFF,0xFF},
						 {0xFF,0xFD,0xBD,0xBD,0xBD,0x3D,0x81,0xBD,0xBD,0xBD,0xBD,0x3D,0xFD,0xFD,0xFF,0xFF,0xBF,0xBF,0xBF,0xBF,0x87,0xB8,0xBF,0xBF,0xBF,0xBF,0xBF,0x80,0xBF,0xBF,0xBF,0xFF},
						 {0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBD,0xBB,0xA7,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xFF,0xFF,0x7F,0xBF,0xDF,0xE7,0xF9,0xFF,0xFF,0xFF,0xFD,0xFB,0xF7,0xCF,0x3F,0xFF,0xFF},
						 {0xFF,0xFF,0xFF,0x01,0x7D,0x7D,0x7D,0x7D,0x7D,0x7D,0x7D,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0x00,0xFF,0xFF,0xFF,0xFF}};
uchar code num[11][16]={{0xFF,0x1F,0xEF,0xF7,0xF7,0xEF,0x1F,0xFF,0xFF,0xF0,0xEF,0xDF,0xDF,0xEF,0xF0,0xFF},
						{0xFF,0xEF,0xEF,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,0xDF,0xC0,0xDF,0xDF,0xFF,0xFF},
						{0xFF,0x8F,0xF7,0xF7,0xF7,0x77,0x8F,0xFF,0xFF,0xCF,0xD7,0xDB,0xDD,0xDE,0xCF,0xFF},
						{0xFF,0xCF,0xF7,0x77,0x77,0xB7,0xCF,0xFF,0xFF,0xE7,0xDF,0xDF,0xDF,0xEE,0xF1,0xFF},
						{0xFF,0xFF,0x3F,0xDF,0xEF,0x07,0xFF,0xFF,0xFF,0xF8,0xFB,0xDB,0xDB,0xC0,0xDB,0xFF},
						{0xFF,0x07,0xF7,0x77,0x77,0xF7,0xF7,0xFF,0xFF,0xE6,0xDE,0xDF,0xDF,0xEE,0xF1,0xFF},
						{0xFF,0x1F,0xEF,0x77,0x77,0xE7,0xFF,0xFF,0xFF,0xF0,0xEE,0xDF,0xDF,0xEE,0xF1,0xFF},
						{0xFF,0xC7,0xF7,0xF7,0x37,0xC7,0xF7,0xFF,0xFF,0xFF,0xFF,0xC0,0xFF,0xFF,0xFF,0xFF},
						{0xFF,0x8F,0x77,0xF7,0xF7,0x77,0x8F,0xFF,0xFF,0xE3,0xDD,0xDE,0xDE,0xDD,0xE3,0xFF},
						{0xFF,0x1F,0xEF,0xF7,0xF7,0xEF,0x1F,0xFF,0xFF,0xFF,0xCE,0xDD,0xDD,0xEE,0xF0,0xFF},
						{0xFF,0xFF,0xFF,0x9F,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0xF3,0xFF,0xFF,0xFF}};	   											   
//延时函数，约2uS*I
void delay_2us(uchar I) 
{
	while(--I); 
}

//延时函数，约1ms*i
void delay_1ms(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void ds1302writebyte(uchar d)
{
	uchar i;
	ACC=d;
	for(i=8;i>0;i--)
	{
		IO=ACC0;
		sclk=1;
		sclk=0;
		ACC>>=1;
	}
}

uchar ds1302readbyte()
{
	uchar i;
	res=1;
	for(i=0;i<8;i++)
	{
		ACC>>=1;
		IO=1;
		ACC7=IO;
		sclk=1;
		sclk=0;
	}
	return (ACC);
}

uchar ds1302read(uchar cmd)
{
	uchar dat;
	res=0;
	sclk=0;
	res=1;
	ds1302writebyte(cmd);
	delay_2us(1);
	dat=ds1302readbyte();
	sclk=1;
	res=0;
	return (dat);
}

void ds1302write(uchar cmd,uchar dat)
{
	res=0;
	sclk=0;
	res=1;
	ds1302writebyte(cmd);
	delay_2us(1);
	ds1302writebyte(dat);
	sclk=1;
	res=0;
}

/*void ds1302writeburst(uchar *P)
{
	uchar i;
	ds1302write(0x8e,0x00);
	res=0;
	sclk=0;
	res=1;
	ds1302writebyte(0xbe);
	for(i=8;i>0;i--)
	{
		ds1302writebyte(*P);
		P++;
	}
	sclk=1;
	res=0;
} */

/*void ds1302readburst(uchar *P)
{
	uchar i;
	res=0;
	sclk=0;
	res=1;
	ds1302writebyte(0xbf);
	for(i=8;i>0;i--)
	{
		*P=ds1302readbyte();
		P++;
	}
	sclk=1;
	res=0;
}	*/

void ds1302start(uchar *P)
{
	uchar i,addr=0x80;
	ds1302write(0x8e,0x00);
	for(i=7;i>0;i--)
	{
		ds1302write(addr,*P);
		P++;
		addr +=2;
	}
	ds1302write(0x8e,0x80);	
}

void ds1302readtime(uchar time[])
{
	uchar i,addr=0x81;
	for(i=0;i<7;i++)
	{
		time[i] = ds1302read(addr);
		addr +=2;
	} 
}

uchar dectobcd(uchar dec)//转换bcd
{
	uchar bcd;
	bcd = 0;
	while(dec >= 10)
	{              
		dec -= 10;                         
		bcd++;
	} 
	bcd <<= 4;
	bcd |= dec;
	return bcd;
}
uchar bcdtodec(uchar bcd)
{
	uchar data1;
	data1 = bcd & 0x0f;     
	bcd = bcd & 0x70;      
	data1 += bcd >> 1;
	data1 += bcd >> 3;    
	return data1;
}
////////////////////////////////////////////////////////////  
void display1()
{
	uchar i;
/*	for(i=0;i<8;i++)
	{
		P1=kong1[i];
		P2=kong2[i];
		delay_2us(200);delay_2us(150);				
	} */
	for(i=0;i<8;i++)
	{
		P1=num[hour/10][i];
		P2=num[hour/10][i+8];
		delay_2us(200);delay_2us(150);			
	}
	for(i=0;i<8;i++)
	{
		P1=num[hour%10][i];
		P2=num[hour%10][i+8];
		delay_2us(200);delay_2us(150);			
	}
	for(i=0;i<8;i++)
	{
		P1=num[10][i];
		P2=num[10][i+8];
		delay_2us(200);delay_2us(150);			
	}
	for(i=0;i<8;i++)
	{
		P1=num[min/10][i];
		P2=num[min/10][i+8];
		delay_2us(200);delay_2us(150);			
	}
	for(i=0;i<8;i++)
	{
		P1=num[min%10][i];
		P2=num[min%10][i+8];
		delay_2us(200);delay_2us(150);			
	}
	for(i=0;i<16;i++)
	{
		P1=xiaonian1[i];
		P2=xiaonian1[i+16];
		delay_2us(200);delay_2us(150);			
	}
	P1=0xff;
	P2=0xff;		
}

void display2()
{
	uchar i;
	switch((sec/2)%6)
	{
		case 0 :  
		{
		/*	for(i=0;i<8;i++)
			{
				P1=kong1[i];
				P2=kong2[i];
				delay_2us(200);delay_2us(150);			
			} */
			for(i=0;i<16;i++)
			{
				P1=guo[i];
				P2=guo[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<8;i++)
			{
				P1=kong1[i];
				P2=kong2[i];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=guo[i];
				P2=guo[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=xiaonian2[i];
				P2=xiaonian2[i+16];
				delay_2us(200);delay_2us(150);			
			}
			P1=0xff;
			P2=0xff;
		} break;
		case 1 :
		{
			for(i=0;i<16;i++)
			{
				P1=tian[i];
				P2=tian[i+16];	   
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=tian[i];
				P2=tian[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=kai[i];
				P2=kai[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=xin[i];
				P2=xin[i+16];
				delay_2us(200);delay_2us(150);			
			}
			P1=0xff;
			P2=0xff;	
		} break;
		case 2 :
		{
			for(i=0;i<8;i++)
			{
				P1=kong1[i];
				P2=kong2[i];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=yao[i];
				P2=yao[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=yao[i];
				P2=yao[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=bang[i];
				P2=bang[i+16];
				delay_2us(200);delay_2us(150);			
			}
		/*	for(i=0;i<16;i++)
			{
				P1=li[i];
				P2=li[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<8;i++)
			{
				P1=kong1[i];
				P2=kong2[i];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=xuan[i];
				P2=xuan[i+16];
				delay_2us(200);delay_2us(150);			
			}
			P1=0xff;
			P2=0xff;*/	
		} break;
		case 3 :
		{
			for(i=0;i<16;i++)
			{
				P1=ni[i];
				P2=ni[i+16];	   
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=xiao[i];
				P2=xiao[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=de[i];
				P2=de[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=yang[i];
				P2=yang[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=zi[i];
				P2=zi[i+16];
				delay_2us(200);delay_2us(150);			
			}
			P1=0xff;
			P2=0xff;	
		} break;
		case 4 :
		{
			for(i=0;i<16;i++)
			{
				P1=zhen[i];
				P2=zhen[i+16];	   
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=ke[i];
				P2=ke[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=ai[i];
				P2=ai[i+16];
				delay_2us(200);delay_2us(150);			
			}				
			P1=0xff;
			P2=0xff;	
		} break;
		case 5 :
		{
			for(i=0;i<16;i++)
			{
				P1=tian[i];
				P2=tian[i+16];	   
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=tian[i];
				P2=tian[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=hao[i];
				P2=hao[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=xin[i];
				P2=xin[i+16];
				delay_2us(200);delay_2us(150);			
			}
			for(i=0;i<16;i++)
			{
				P1=qing[i];
				P2=qing[i+16];
				delay_2us(200);delay_2us(150);			
			}
			P1=0xff;
			P2=0xff;	
		} break;
	}	
}

void display3()
{
	uchar i;
	if(n/20==0)
	{
	/*	for(i=0;i<8;i++)
		{
			P1=kong1[i];
			P2=kong2[i];
			delay_2us(200);delay_2us(150);			
		} */
		for(i=0;i<8;i++)
		{
			P1=num[2][i];
			P2=num[2][i+8];
			delay_2us(200);delay_2us(150);			
		}
		for(i=0;i<8;i++)
		{
			P1=num[0][i];
			P2=num[0][i+8];
			delay_2us(200);delay_2us(150);			
		}
		for(i=0;i<8;i++)
		{
			P1=num[year/10][i];
			P2=num[year/10][i+8];
			delay_2us(200);delay_2us(150);		
	
		}
		for(i=0;i<8;i++)
		{
			P1=num[year%10][i];
			P2=num[year%10][i+8];
			delay_2us(200);delay_2us(150);			
		}
		for(i=0;i<16;i++)
		{
			P1=nian[i];
			P2=nian[i+16];
			delay_2us(200);delay_2us(150);			
		}
		for(i=0;i<16;i++)
		{
			P1=xiaonian3[i];
			P2=xiaonian3[i+16];
			delay_2us(200);delay_2us(150);			
		}
		P1=0xff;
		P2=0xff;
		
	}
	if(n/20==1)
	{
	/*	for(i=0;i<4;i++)
		{
			P1=kong1[i];
			P2=kong2[i];
			delay_2us(200);delay_2us(150);			
		} */
		for(i=0;i<8;i++)
		{
			P1=num[month/10][i];
			P2=num[month/10][i+8];
			delay_2us(200);delay_2us(150);			
		}
		for(i=0;i<8;i++)
		{
			P1=num[month%10][i];
			P2=num[month%10][i+8];
			delay_2us(200);delay_2us(150);			
		}
		for(i=0;i<4;i++)
		{
			P1=kong1[i];
			P2=kong2[i];
			delay_2us(200);delay_2us(150);				
		}
		for(i=0;i<16;i++)
		{
			P1=yue[i];
			P2=yue[i+16];
			delay_2us(200);delay_2us(150);			
		}
		for(i=0;i<4;i++)
		{
			P1=kong1[i];
			P2=kong2[i];
			delay_2us(200);delay_2us(150);				
		}
		for(i=0;i<8;i++)
		{
			P1=num[day/10][i];
			P2=num[day/10][i+8];
			delay_2us(200);delay_2us(150);			
		}
		for(i=0;i<8;i++)
		{
			P1=num[day%10][i];
			P2=num[day%10][i+8];
			delay_2us(200);delay_2us(150);			
		}
		for(i=0;i<4;i++)
		{
			P1=kong1[i];
			P2=kong2[i];
			delay_2us(200);delay_2us(150);				
		}
		for(i=0;i<16;i++)
		{
			P1=xingq[6][i];
			P2=xingq[6][i+16];
			delay_2us(200);delay_2us(150);			
		}
		P1=0xff;
		P2=0xff;		
	}
	if(n/20==2)
	{
		for(i=0;i<16;i++)
		{
			P1=xing[i];
			P2=xing[i+16];
			delay_2us(200);delay_2us(150);			
		}
		for(i=0;i<16;i++)
		{
			P1=qi[i];
			P2=qi[i+16];
			delay_2us(200);delay_2us(150);			
		}
		for(i=0;i<4;i++)
		{
			P1=kong1[i];
			P2=kong2[i];
			delay_2us(200);delay_2us(150);				
		}
		for(i=0;i<16;i++)
		{
			P1=xingq[weak-1][i];
			P2=xingq[weak-1][i+16];
			delay_2us(200);delay_2us(150);			
		}
		P1=0xff;
		P2=0xff;	
	}
	if(n>=60)
		n=0;
}

void inter0() interrupt 0
{
	n++;
	k=~k;
	if(k==0)
	{
		switch(a)
		{
			case 0xf0 : 
			{delay_1ms(68);
			display3();} break;
			case 0x0f : 
			{delay_1ms(68);
			display2();} break;
			default : 
			{delay_1ms(68);
			display1();	}
		}	
	}		
}
			  
///////////////////////////////////////////	   
void main(void)
{
	uchar c=0;
	P0=0xff;
	EX0=1;
	IT0=1;
	EA=1;
	while(1)
	{
		ds1302readtime(time);
		sec=  bcdtodec(time[0]);
		min=  bcdtodec(time[1]);
		hour= bcdtodec(time[2]);
		day=  bcdtodec(time[3]);
		month=bcdtodec(time[4]);
		weak= bcdtodec(time[5]);
		year= bcdtodec(time[6]);
		if(!key1)
		{
			delay_1ms(20);
			if(!key1)
			{
				a=0x00;		
			}			
		}
		if(!key2)
		{
			delay_1ms(20);
			if(!key2)
			{
				a=0xf0;
			}				
		}
		while(!key1&&!key2)
		{
			P1=~time[0];
			P2=~time[1];
			delay_1ms(300);
			ds1302readtime(time);
					
		}
		P1=0xff;
		P2=0xff;
		if(!key3)
		{
			delay_1ms(20);
			while(!key3)
			{
				c++;
				delay_1ms(30);
			}
			if(c>60)
			{
				EA=0;
				P1=0x00;
				P2=0x00;
				delay_1ms(500);  				
				c=0xff;
				while(key3)
				{
					if(!key2)
					{
						delay_1ms(20);
						if(!key2)
						{
							year++;		
							if(year==99)
							year=0;
						}
					} 								
					P1=~dectobcd(year);
					P2=0x7f|(~c);
					delay_1ms(200);									
				}
				delay_1ms(250);
				while(key3)
				{
					if(!key2)
					{
						delay_1ms(20);
						if(!key2)
						{
							month++; 						
							if(month==13)
							month=1;
						}
					}
					P1=~dectobcd(month);
					P2=0xbf|(~c);
					delay_1ms(200);				
				}		
				delay_1ms(250);		
				while(key3)
				{
					if(!key2)
					{
						delay_1ms(20);
						if(!key2)
						{
							day++;
							if((month==1)||(month==3)||(month==5)||(month==7)||(month==8)||(month==10)||(month==12))
							{
								if(day==32)
								day=0;
							}
							else if((month==2)&&(year%4==0))
							{
								if(day==30)
								day=0;
							}
							else if((month==2))
							{
								if(day==29)
								day=0;
							}
							else
							{
								if(day==31)
								day=0;
							}

						}
					}
					P1=~dectobcd(day);
					P2=0xdf|(~c);
					delay_1ms(200);					
				}
				delay_1ms(250);
				while(key3)
				{
					if(!key2)
					{
						delay_1ms(20);
						if(!key2)
						{
							weak++;
							if(weak==8)
							weak=1;
						}
					}
					P1=~dectobcd(weak);
					P2=0xef|(~c);
					delay_1ms(200);					
				}
				delay_1ms(250);
				while(key3)
				{
					if(!key2)
					{
						delay_1ms(20);
						if(!key2)
						{
							hour++;
							if(hour==24)
							hour=0;
						}
					}
					P1=~dectobcd(hour);
					P2=0xf7|(~c);
					delay_1ms(200);					
				}
				delay_1ms(250);
				while(key3)
				{
					if(!key2)
					{
						delay_1ms(20);
						if(!key2)
						{
							min++;
							if(min==60)
							min=0;
						}
					}
					P1=~dectobcd(min);
					P2=0xfb|(~c);
					delay_1ms(200);					
				}
				delay_1ms(250);
				while(key3);
				time[0]=0x01;
				time[1]=dectobcd(min);
				time[2]=dectobcd(hour);
				time[3]=dectobcd(day);
				time[4]=dectobcd(month);
				time[5]=dectobcd(weak);
				time[6]=dectobcd(year);	
				ds1302start(time);
				P1=0x00;
				P2=0x00;
				delay_1ms(300);
				P1=0xff;
				P2=0xff;
				EA=1;	
			}
			a=0x0f;
		}  			
	} 		
}

