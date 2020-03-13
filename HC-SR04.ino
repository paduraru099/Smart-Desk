
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include<LiquidCrystal.h>


long a;

int x=900;
int x2=0;
int goUpFlag = 0;
long duration;
int distance;
LiquidCrystal lcd(1, 2, 3, 4, 5, 6);
int soundPin = A0;





ISR (TIMER1_COMPA_vect)
{
      lcd.clear();
         lcd.print("Distance:");
         lcd.print(x2);
         lcd.setCursor(0,1);


         if(a < 0.875*2*x2)
         lcd.print("Too close");
         else if ( a>=0.875*2*x2 && a<=2*x2 )
         lcd.print("Almost");
         else
         lcd.print("Proper Distance");
         
}

int main(){

  
  lcd.begin(16,2);
 



  DDRB|=(1<< PB0);
  DDRB|=(1<< PB1);
  DDRB |= (1 << PB4);
  DDRB &=~(1 << PB3);
  DDRC &=~(1 << PC4);
  DDRC &=~(1 << PC5);
  


   OCR1A = 0x3D08;

    TCCR1B |= (1 << WGM12);
    // Mode 4, CTC on OCR1A

    TIMSK1 |= (1 << OCIE1A);
    //Set interrupt on compare match

    TCCR1B |= (1 << CS12) | (1 << CS10);
    // set prescaler to 1024 and start the timer


    sei();
    // enable interrupts

 
  

  
while(1){

       
          
 
          
      
          PORTB &= ~( 1 << PB4);
          delayMicroseconds(2);  
          PORTB |= (1 << PB4);
          delayMicroseconds(10);
          PORTB &= ~( 1 << PB4);  
          duration = pulseIn(11, HIGH);
          distance= duration*0.034/2;

          
            
            if ( PINC & (1<<4) )
            {
              if(goUpFlag == 0)
              {
                goUpFlag = 1;
              }
                x++;
            }

            if ( !(PINC & (1<<4)) && (goUpFlag == 1))
            {
                x = x - x%100;
            }


             if ( PINC & (1<<5) && x>0 )
            {
              if(goUpFlag == 1)
              {
                goUpFlag = 0;
              }
                x--;
                
            }

            if ( !(PINC & (1<<5)) && (goUpFlag == 0))
            {
              if(x%100 != 0)
              {
                x = x +(100- x%100);
              }
            }
                x2=x/100;
            //Serial.println(x);
            //Serial.println(x2);
            //Serial.println(' ');
          
          //Serial.print("Distance: ");
          //Serial.println(distance);
           
     
           
           a = distance;

      
    
      if( a > 2*x2 )
      {
         
         PORTB |= (1 << PB1);
         PORTB &= ~(1 << PB0);
         PORTB &= ~(1 << PB2);
         
      }
      else if ( 0.70*2*x2<=a && a<=2*x2 )
      {
         
         
         
         tone(soundPin, 200, 100);
         PORTB |= (1 << PB2);
         PORTB &= ~(1 << PB0);
         PORTB &= ~(1 << PB1);
      }

      else {
         
         
           
         tone(soundPin, 400, 200);
         PORTB |= (1<<PB0);
         PORTB &= ~(1 << PB1);
         PORTB &= ~(1 << PB2);
         
      }

      

      
          
}
  
     return 0;
  }
  

 



   
 
