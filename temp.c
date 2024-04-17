#include<reg51.h>
sbit rs = P3^5;
sbit rw = P3^6;
sbit en = P3^7;
sbit wr1 = P3^0;
sbit rd1 = P3^1;
sbit intr = P3^2;
sfr adc = 0xA0;

void delay(unsigned int msec)
{
	int i,j;
	for (i=0; i<msec; i++)
	for (j=0; j<1275; j++)
	{}
	}

	void lcdcmd(unsigned char item)
	{
		P1 = item;
		rs = 0;
		rw = 0;
		en = 1;
		delay(5);
		en = 0;
	}
	
	void lcddata(unsigned char item)
	{
		P1 = item;
		rs = 1;
		rw = 0;
		en = 1;
		delay(5);
		en = 0;
	}
	void lcd(unsigned char *item)
	{
		unsigned int x;
		for (x=0; item[x]!=0; x++)
		lcddata(item[x]);
	}
	
	void main()
	{
		unsigned int z1, z2, z3, a, b, c, d, value;
		lcdcmd(0x38);
		delay(10);
		lcdcmd(0x0E);
		delay(10);
		adc = 0xFF;
		lcd("temp");
		intr = 1;
		rd1 = 1;
		wr1 = 1;
		while(1)
		{
			wr1 = 0;
			delay(100);
			wr1 = 1;
			while(intr == 1);
			rd1 = 0;
			delay(100);
			value = adc*1.96;
			a = value/100;
			b = value%100;
			c = b/10;
			d = b%10;
			z1 = a+0x30;
			z2 = c+0x30;
			z3 = d+0x30;
			delay(10);
			lcdcmd(0x88);
			delay(10);
			lcddata(z1);
			delay(10);
			lcdcmd(0x8A);
			delay(z2);
			delay(10);
			lcdcmd(0x8B);
			delay(10);
			lcddata(z3);
			delay(10);
			rd1 = 1;
		}
	}
	
		
		
