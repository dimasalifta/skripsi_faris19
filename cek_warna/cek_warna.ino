
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

byte gammatable[256];      
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);  
LiquidCrystal_I2C lcd(0x27,16,2);  

#define commonAnode false  
void setup()
{

  Serial.begin(9600);
  lcd.init();
  lcd.backlight(); 
  
  lcd.begin(16,2);              
  lcd.clear();                  
  lcd.setCursor(1,0);           
  lcd.print("ArduinoKita");
  delay(3000);  

  lcd.setCursor(4,1);
  if (tcs.begin())          
  {
    lcd.print("Ready");
  } 
  else
  {
    lcd.print("Sensor Error");
    while (1);
  }

  
}



void loop()
{

    float red, green, blue;                        
    tcs.setInterrupt(false);      
    delay(60);                   
    tcs.getRGB(&red, &green, &blue);  
    tcs.setInterrupt(true);
    delay(500);                     
    lcd.clear();                  
    lcd.print("Warna: ");   
    lcd.setCursor(0,1);
    lcd.print("R:");
    lcd.print(int(red));
    lcd.print(" G:");
    lcd.print(int(green));
    lcd.print(" B:");
    lcd.print(int(blue));
    
/////////////////////////////////////////////////////1
  if(red>=140 & red<=185 & green>=30 & green<=60 & blue>=40 & blue<=50) {
  lcd.setCursor(10,0);          
  lcd.print("Merah");
  
  }
  /////////////////////////////////////////////////////2
  if(red>=35 & red<=55 & green>=75 & green<=85 & blue>=110 & blue<=130){
  lcd.setCursor(10,0);           
  lcd.print("Biru");

   }
  /////////////////////////////////////////////////////3
  if(red>=50 & red<=70 & green>=105 & green<=135 & blue>=50 & blue<=80) {
  lcd.setCursor(10,0);         
  lcd.print("Hijau");
    
  }
  
    delay(1000);
}
