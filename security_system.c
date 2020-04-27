/*
 * security_system.c
*/ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
unsigned char store[3][4] ={
							{0,0,0},
							{0,0,0},
							{0,0,0},
							{0,0,0}
							};
int a,c,d,e,f,g;
char buff[1];
int i,j;
int temp=1000, temp1=1000, 
temp2=1000, temp3=1000, 
temp4=1000, temp5=1000,
temp6=1000,temp7=1000;
unsigned char password[3][4];

void command(unsigned char c);
void display(unsigned char d);
void string (unsigned char *a);


void command(unsigned char c)
{
	PORTB=c&(0xF0);
	PORTD&=0xfe;
	PORTD|=0x02;
	_delay_ms(5);
	PORTD&=0xFD;
	_delay_ms(1);

	PORTB=(c<<4)&(0xF0);
	_delay_ms(5);

	PORTD&=0xfe;
	_delay_ms(5);

	PORTD|=0x02;
	_delay_ms(5);
	PORTD&=0xFD;
}
void display(unsigned char d)
{
	PORTB=d&(0xF0);
	PORTD|=0x01;
	_delay_ms(5);

	PORTD|=0x02;
	_delay_ms(5);
	PORTD&=0xFD;
	_delay_ms(5);

	PORTB=(d<<4)&(0xF0);
	_delay_ms(5);

	PORTD|=0x01;
	_delay_ms(5);

	PORTD|=0x02;
	_delay_ms(5);
	PORTD&=0xFD;
	_delay_ms(5);
}
void string(unsigned char *a)
{
	while ( *a!='\0' )
	{
		display(*a) ;
		a++ ;
	}
}

void compare()
{
	int var,i,j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<4;j++)
		{
			if (!(password[i][j]==store[i][j]))
			{
			    PORTD=0x40;
				command(0x01);
				string("Match Not Found");
				command(0xc0);
				string("Access Denied");
				return;
			}
			else
			{
				continue;
			}
		}
	}
		PORTD=0x80;
		command(0x01);
		string("Match Found");
		command(0xc0);
		string("Access Granted");
	return;
 }
  void scan1(unsigned int sensr,unsigned int name)
  {
	  if (name==1)
	  {
		  if(sensr>180 && sensr<310)
		  {
			  store[0][0]=1;
			   _delay_ms(1);
			  PORTC|=0x01;	  
		  }
		  else if(sensr>120 && sensr<165)
		  {
			  store[1][0]=1;
			   _delay_ms(1);
			  PORTC|=0x02;
		  }
		  else if(sensr>100 && sensr<110)
		  {
			  store[2][0]=1;
			   _delay_ms(1);
     		  PORTC|=0x04;
		  }
	  }
 
	 else if (name==2)
	  {
		  if(sensr>179 && sensr<320)
		  {
			  store[0][1]=1;
			   _delay_ms(1);
			  PORTC|=0x08;	  
		  }
		  else if(sensr>130 && sensr<168)
		  {
			  store[1][1]=1;
			   _delay_ms(1);
			  PORTC|=0x10;	  
		  }
		  else if(sensr>100 && sensr<125)
		  {
			  store[2][1]=1;
			  _delay_ms(1); 
			  PORTC|=0x20;
		  }
	  }
	 else if (name==3)
	  {
		  if(sensr>180 && sensr<308)
		  {
			  store[0][2]=1;
			  _delay_ms(1);
			  PORTC|=0x40;	  
		  }
		  else if(sensr>124 && sensr<166)
		  {
			  store[1][2]=1;
			   _delay_ms(1);
			  PORTC|=0x80;
		  }
		  else if(sensr>104 && sensr<120)
		  {
			  store[2][2]=1;
			   _delay_ms(1);
			  PORTD|=0x04;	  
		  }
	  }
	    else if (name==4)
	  {
		  if(sensr>200 && sensr<340)
		  {
			  store[0][3]=1;
			  _delay_ms(1);
			  PORTD|=0x08;	  
		  }
		  else if(sensr>132 && sensr<195)
		  {			  
			  store[1][3]=1;
			  _delay_ms(1);
        	  		PORTD|=0x10;  
		  }
		  else if(sensr>100 && sensr<130)
		  {
			  store[2][3]=1;
			  _delay_ms(1);
			  PORTD|=0x20;	  
		  }
	  }
  }
void scan()
{
	while(1)
	{
//---------Activate ADC CHANNEL 1: start---------//           
		   command(0x80);
			ADMUX=0x40;
	        _delay_ms(100);
	        ADCSRA=0xe7;
	        _delay_ms(100);
			
			for(int i=0;i<=20;i++)
			{
	        while (!(ADCSRA &(1<<ADIF)));
			c=ADC;
			c=c/2;
			ADCSRA|=(1<<ADIF);
			
			if(c<=temp)
			temp=c;
			}
			sprintf(buff,"%4d",c);
			string(buff);
			scan1(temp,1);
//---------Activate ADC CHANNEL 1: stop---------//         
//---------Activate ADC CHANNEL 2: start---------//                
                      	            
command(0xc0);
			ADMUX=0x41;
			_delay_ms(100);
			ADCSRA=0xe7;
			_delay_ms(100);		
			for(int i=0;i<=20;i++)
	           {
			while (!(ADCSRA &(1<<ADIF)));
			e=ADC;
			e=e/2;
			
			if(e<=temp1)
			temp1=e;
		}
			sprintf(buff,"%4d",e);
			string(buff);
			scan1(temp1,2);
//---------Activate ADC CHANNEL 2: stop---------//         
//---------Activate ADC CHANNEL 3: start---------//         
command(0x85);
			ADMUX=0x42;
			_delay_ms(100);
			ADCSRA=0xe7;
			_delay_ms(100);	
			for(int i=0;i<=20;i++)
		{
			while (!(ADCSRA &(1<<ADIF)));
			f=ADC;
			f=f/2;
		            if(f<=temp2)
			temp2=f;
		}
			sprintf(buff,"%4d",f);
		            string(buff);
			 scan1(temp2,3);

//---------Activate ADC CHANNEL 3: stop---------//
//---------Activate ADC CHANNEL 4: start---------//                  
			command (0xc5);
			 ADMUX=0x43;
			_delay_ms(100);
			ADCSRA=0xe7;
			_delay_ms(100);
			for(int i=0;i<=20;i++)
			{
			while (!(ADCSRA &(1<<ADIF)));
			g=ADC;
			g=g/2;
                     		if(g<=temp3)
			temp3=g;
		}
			sprintf(buff,"%4d",g);
			string(buff);
			scan1(temp3,4);
//---------Activate ADC CHANNEL 4: stop---------//         	

		if((PINB&0x01)==0x01)        // if switch 1 is active
	  {
		  a=(PINB&0b00000001);
		  while(a!=0x00)
                    {
		  a=(PINB&0b00000001);
	         }
		  command(0x01);
		  string("Scan Complete");
		  PORTC=0x00;
		//  PORTD=0b000000011;
		temp=1000;
		temp1=1000;
		temp2=1000;
		temp3=1000;
	   return;
	  }	
	  else
	  {
		  continue;
	  }
	}	  
}
void recreate()
{
	unsigned char i,j;
	command(0x01);
	for (i=0;i<3;i++)
	{
		for (j=0;j<4;j++)
		{
			store[i][j]=0;
		}
	}
	while(1)
	{
		command(0x80);
		ADMUX=0x40;
		_delay_ms(100);
		ADCSRA=0xe7;
		_delay_ms(100);	
		for(int i=0;i<=20;i++)
	{
		while (!(ADCSRA &(1<<ADIF)));
		c=ADC;
		c=c/2;
		ADCSRA|=(1<<ADIF);	
		if(c<=temp4)
		temp4=c;
	}
		sprintf(buff,"%4d",c);
		string(buff);
		scan1(temp4,1);
		command(0xc0);
		ADMUX=0x41;
		_delay_ms(100);
		ADCSRA=0xe7;
		_delay_ms(100);
		for(int i=0;i<=20;i++)
	{
		while (!(ADCSRA &(1<<ADIF)));
		e=ADC;
		e=e/2;	
		if(e<=temp5)
		temp5=e;
	}
		sprintf(buff,"%4d",e);
		string(buff);
		scan1(temp5,2);


		command(0x85);
		ADMUX=0x42;
		_delay_ms(100);
		ADCSRA=0xe7;
		_delay_ms(100);

			for(int i=0;i<=20;i++)
			{

		while (!(ADCSRA &(1<<ADIF)));
		f=ADC;
		f=f/2;
		
		if(f<=temp6)
			temp6=f;
			}
			sprintf(buff,"%4d",f);
		string(buff);
		scan1(temp6,3);


		command (0xc5);
		ADMUX=0x43;
		_delay_ms(100);
		ADCSRA=0xe7;
		_delay_ms(100);
			for(int i=0;i<=20;i++)
			{

		while (!(ADCSRA &(1<<ADIF)));
		g=ADC;
		g=g/2;
		
		if(g<=temp7)
			temp7=g;
			}
			sprintf(buff,"%4d",g);
		string(buff);
		scan1(temp7,4);	
	
		
		if((PINB&0x04)==0x04)
		{
		a=(PINB&0b00000100);
		while(a!=0x00)
		{
			a=(PINB&0b00000100);
		}
		command(0x01);
		string("Recreate Complete");
		  PORTC=0x00;
		  //PORTD=0b000000011;
		temp4=1000;
		temp5=1000;
		temp6=1000;
		temp7=1000;
		return;	 
		}
		else
		{
			continue;
		}
	} 
}
void store1()
{
	for (i=0;i<3;i++)
	{
		for (j=0;j<4;j++)
		{
			password[i][j]=store[i][j];
		}
	}
	command(0x01);
	string("Password Saved");
	return;
}

void lcd_init()
{
	command(0x32);
	_delay_ms(1);

	command(0x28);
	_delay_ms(1);

	command(0x06);
	_delay_ms(1);

	command(0x0e);
	_delay_ms(1);

	command(0x01);
	_delay_ms(1);

	command(0x80);
	_delay_ms(1);
}

int main(void)

{   
	MCUCSR|=(1<<JTD);
	MCUCSR|=(1<<JTD);
	
	unsigned char a;

	DDRD=0xFF;
	DDRC=0xFF;

	PORTC=0b00000000;
	PORTD=0b00000011;

	DDRB=0xF0;;
	DDRA=0x00;

	lcd_init();

while(1)
{
	if((PINB&0x01)==0x01)
	{
	  	a=(PINB&0b00000001);
		while(a!=0x00)
		{
		  	a=(PINB&0b00000001);
	  	}
		scan();
	}
	
	else if((PINB&0x02)==0x02)
	{
		a=(PINB&0b00000010);
		while(a!=0x00)
		{
			a=(PINB&0b00000010);
		}
		store1();
	       
	}   
	else if((PINB&0x04)==0x04)
	{
		a=(PINB&0b00000100);
		while(a!=0x00)
		{
			a=(PINB&0b00000100);
		}
		 recreate();
    }
	   

	else if((PINB&0x08)==0x08)
	{
		a=(PINB&0b00001000);
		while(a!=0x00)
		{
			a=(PINB&0b00001000);
		}
		compare();
	}
	else
	{
		continue;
	}
  }
}