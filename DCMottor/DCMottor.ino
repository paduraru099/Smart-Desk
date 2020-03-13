#include <SimpleDHT.h>
// include the library code:
#include <LiquidCrystal.h>



// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


int pinDHT11 = 2;
SimpleDHT11 dht11;

#define ENABLE PD5
#define DIRA PD3
#define DIRB PD4

int i;

 
void setup() {
  //---set pin direction
  

  DDRD |= (1<<PD5);

  DDRD |= (1<<PD3);

  DDRD |= (1<<PD4);
  Serial.begin(9600);
  PORTD |= (1 << PD5); //enable
       PORTD |= (1 << PD4);
       PORTD &= ~(1 << PD3);

 
  // Print a message to the LCD.
  lcd.clear();
  lcd.begin(16,2);
  lcd.print("Ventilator vruum");

}
 byte temperature;
  byte humidity;


  

void loop() {


    
    // start working...
  
  // read with raw sample data.
 
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    
    Serial.print("Read DHT11 failed");
    

  }

  
  lcd.setCursor(0,1);
  lcd.print("Temperature: ");
  lcd.print(temperature);
 

  
  // DHT11 sampling rate is 1HZ.
  delay(1000);

  if (temperature < 25)
  {
     PORTD &= ~(1 << PD5); //disable ventilator
       PORTD &= ~(1 << PD4);
       PORTD |= (1 << PD3);
  }
  else
  {
     PORTD |= (1 << PD5); //enable ventilator
       PORTD |= (1 << PD4);
       PORTD &= ~(1 << PD3);
  }
 
}
   
