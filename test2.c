#include <LiquidCrystal.h>
#include <util/delay.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

char ocitaj_taster()
{
  char taster = 0;
  unsigned char row;
  
  MCUCR &= ~0x10;
  PORTD = 0x0f; 
  
  for(row = 0x80; row != 0x08; row >>= 1)
  {
    DDRD = row;
	_delay_ms(2);
    
    switch(row | ((~PIND) & 0x0f))
    {
      case 0x88:
      	taster = '1'; break;
      case 0x84:
      	taster = '2'; break;
      case 0x82:
      	taster = '3'; break;
      case 0x81:
      	taster = 'A'; break;
		
	  case 0x48:
      	taster = '4'; break;
      case 0x44:
      	taster = '5'; break;
      case 0x42:
      	taster = '6'; break;
      case 0x41:
      	taster = 'B'; break;
		
	  case 0x28:
      	taster = '7'; break;
      case 0x24:
      	taster = '8'; break;
      case 0x22:
      	taster = '9'; break;
      case 0x21:
      	taster = 'C'; break;
		
	  case 0x18:
      	taster = '*'; break;
      case 0x14:
      	taster = '0'; break;
      case 0x12:
      	taster = '#'; break;
      case 0x11:
      	taster = 'D'; break;
    }
  }
  
  return taster;
}

byte herc[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

byte karo[8]=
{
  B00100,
  B01110,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};
byte tref[8]=
{
  B00100,
  B01110,
  B00100,
  B10101,
  B11111,
  B01110,
  B00100,
  B00000
  
};
byte pik[8]=
{
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
  B11111,
  B01010,
  B00000
  
};



int main()
{
  	lcd.begin(16, 2);
  	lcd.createChar(0,pik);
  	lcd.createChar(1,karo);
    lcd.createChar(2,herc);
    lcd.createChar(3,tref);
    lcd.setCursor(0, 0);
  
  	char niz[4];
  	lcd.print("Pritisni '*'");
     	
   while(1)
    {
    	
      	char taster=ocitaj_taster();
      	if(taster=='*')
        {
          	lcd.clear();
        	for(int i=0;i<4;i++)
            { 
              int broj=random(3);
              lcd.setCursor(i,0);
              niz[i]=byte(broj);
              lcd.write(byte(broj));
              
            }
          	_delay_ms(2000);
          	lcd.clear();
          	niz[4]='\0';
          	
          	
          	
            lcd.print("----");
          	lcd.setCursor(0,0);
      
          	lcd.blink();
          
          	int k=0,m=0,i=0;
          	char novi_niz[4];
          	char prethodni_taster1=0,prethodni_taster2=0,prethodni_taster3=0,prethodni_taster4=0;
          	while(1)
            {
              	char taster=ocitaj_taster();
          		if( taster=='6' && prethodni_taster1!=taster)
                {
                  prethodni_taster1=taster;
                  if(k<4)
                  {  
                  	lcd.setCursor(++k,0);
                    lcd.blink();
                	}
                  else
                  {
                    k=0;
                  	lcd.setCursor(0,0);
                    lcd.blink();
                  }
                }
              	if(taster!='4')
                  prethodni_taster1=0;
         
              
              	if( taster=='4' && prethodni_taster2!=taster)
                {
                  prethodni_taster2=taster;
                  if(k>0)
                  {  
                    
                  	lcd.setCursor(--k,0);
                	
                    lcd.blink();
                	}
                  else
                  {
                    k=3;
                  	lcd.setCursor(0,0);
                    
                    lcd.blink();
                  }
                }
              	if(taster!='4')
                  prethodni_taster2=0;
              	
              	
              	if( taster=='2' && prethodni_taster3!=taster)
                {
                  prethodni_taster3=taster;
                  if(m<4)
                  {	m++;
                   	novi_niz[i]=byte(m);
                   	lcd.setCursor(k,0);
                    lcd.write(byte(m));
                    i++;
                  }
                  else
                    m=0;
                }
              	if(taster!='2')
                  prethodni_taster3=0;
              	
                if( taster=='8' && prethodni_taster4!=taster)
                {
                  prethodni_taster4=taster;
                  if(m>0)
                  {	m--;
                   	novi_niz[i]=byte(m);
                    lcd.setCursor(k,0);
                    lcd.write(byte(m));
                    i++;
                  }
                  else
                    m=3;
                }
              	if(taster!='8')
                  prethodni_taster4=0;
              
              	if(taster=='5')
                  break;
            }
          novi_niz[4]='\0';
         
          if(!strcmp(niz,novi_niz))
   			 {
      			lcd.setCursor(0,1);
      			lcd.print("Tacno");
    		  }
  		  else 
    		{   
      			lcd.setCursor(0,1);
      			lcd.print("Netacno");
    
    		}
        }
    }
  	
	
  
  	return 0;
}