//Include the library
#include <MQUnifiedsensor.h>
//Arduino to NodeMCU Lib
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

String str;
int rn, bn, gn;
/************************Hardware Related Macros************************************/
#define         Board                   ("Arduino UNO")
#define         Pin_MQ2                     (A0)  //Analog input 3 of your arduino
#define         Pin_MQ4                     (A1)  //Analog input 3 of your arduino
#define         Pin_MQ5                     (A2)  //Analog input 3 of your arduino
#define         Pin_MQ9                     (A3)  //Analog input 3 of your arduino

#define         Pin_MQ3                     (A0)  //Analog input 3 of your arduino
#define         Pin_MQ7                     (A1)  //Analog input 3 of your arduino
#define         Pin_MQ8                     (A2)  //Analog input 3 of your arduino
#define         Pin_MQ135                   (A3)  //Analog input 3 of your arduino

#define         Pin_MQ6                     (A0)  //Analog input 3 of your arduino

/***********************Software Related Macros************************************/
#define         Type_MQ2                    ("MQ-2") //MQ2
#define         Type_MQ3                    ("MQ-3") //MQ2
#define         Type_MQ4                    ("MQ-4") //MQ2
#define         Type_MQ5                    ("MQ-5") //MQ2
#define         Type_MQ6                    ("MQ-6") //MQ2
#define         Type_MQ7                    ("MQ-7") //MQ2
#define         Type_MQ8                    ("MQ-8") //MQ2
#define         Type_MQ9                    ("MQ-9") //MQ2
#define         Type_MQ135                  ("MQ-135") //MQ2


#define         Voltage_Resolution      (5)
#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO
#define         RatioMQ2CleanAir        (9.83) //RS / R0 = 9.83 ppm 
#define         RatioMQ3CleanAir        (60) //RS / R0 = 9.83 ppm 
#define         RatioMQ4CleanAir        (4.4) //RS / R0 = 9.83 ppm 
#define         RatioMQ5CleanAir        (6.5) //RS / R0 = 9.83 ppm 
//#define         RatioMQ6CleanAir        (10) //RS / R0 = 9.83 ppm
#define         RatioMQ7CleanAir        (27.5) //RS / R0 = 9.83 ppm 
#define         RatioMQ8CleanAir        (70) //RS / R0 = 9.83 ppm 
#define         RatioMQ9CleanAir        (9.6) //RS / R0 = 9.83 ppm 
#define         RatioMQ135CleanAir      (3.6) //RS / R0 = 9.83 ppm 
//>>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >
//PILIH 4 SAJA

//MQUnifiedsensor S0(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin_MQ2, Type_MQ2);
//MQUnifiedsensor S1(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin_MQ4, Type_MQ4);
//MQUnifiedsensor S2(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin_MQ5, Type_MQ5);
//MQUnifiedsensor S3(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin_MQ9, Type_MQ9);

MQUnifiedsensor S0(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin_MQ3, Type_MQ3);
MQUnifiedsensor S1(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin_MQ7, Type_MQ7);
MQUnifiedsensor S2(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin_MQ8, Type_MQ8);
MQUnifiedsensor S3(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin_MQ135, Type_MQ135);
//>>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>


//Initialise Arduino to NodeMCU (5=Rx & 6=Tx)
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_2_4MS, TCS34725_GAIN_60X);

SoftwareSerial nodemcu(5, 6);
void setup() {
  //Init the serial port communication - to debug the library
  Serial.begin(9600); //Init serial port
  nodemcu.begin(9600);
  delay(1000);
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
  lcd.init();                      // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  //Set math model to calculate the PPM concentration and the value of constants
  S0.setRegressionMethod(1); //_PPM =  a*ratio^b
  S1.setRegressionMethod(1); //_PPM =  a*ratio^b
  S2.setRegressionMethod(1); //_PPM =  a*ratio^b
  S3.setRegressionMethod(1); //_PPM =  a*ratio^b


  //>>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>

  //  //PILIH 4 SAJA
  //  S0.setA(658.71); S0.setB(-2.168); // mq2 propana (C3H8)
  //  S1.setA(1012.7); S1.setB(-2.786); // mq4 methana (CH4)
  //  S2.setA(80.897); S2.setB(-2.431); // mq5 LPG (C3H8 + C4H10)
  //  S3.setA(1000.5); S3.setB(-2.186); // mq9 LPG (C3H8 + C4H10)



  S0.setA(0.3934); S0.setB(-1.504); // mq3 alkohol (C2H6O)
  S1.setA(99.042); S1.setB(-1.518); // mq7 karbon monoksida (CO)
  S2.setA(976.97); S2.setB(-0.688); // mq8 hidrogen (H2)
  S3.setA(102.2); S3.setB(-2.473);  // mq135 amonia (NH3)
  //>>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >>> >> .

  //  S0.setA(1009.2); S0.setB(-2.35);  // mq6 LPG (C3H8 + C4H10)


  S0.init();
  S1.init();
  S2.init();
  S3.init();
  Serial.print("Calibrating please wait.");
  lcd.setCursor(0, 0);
  lcd.print("Kalibrasi.");

  float calcR0_S0 = 0;
  float calcR0_S1 = 0;
  float calcR0_S2 = 0;
  float calcR0_S3 = 0;
  for (int i = 1; i <= 10; i ++)
  {
    S0.update(); // Update data, the arduino will be read the voltage on the analog pin
    S1.update(); // Update data, the arduino will be read the voltage on the analog pin
    S2.update(); // Update data, the arduino will be read the voltage on the analog pin
    S3.update(); // Update data, the arduino will be read the voltage on the analog pin
    //    calcR0_S0 += S0.calibrate(RatioMQ2CleanAir);
    //    calcR0_S1 += S1.calibrate(RatioMQ4CleanAir);
    //    calcR0_S2 += S2.calibrate(RatioMQ5CleanAir);
    //    calcR0_S3 += S3.calibrate(RatioMQ9CleanAir);

    calcR0_S0 += S0.calibrate(RatioMQ3CleanAir);
    calcR0_S1 += S1.calibrate(RatioMQ7CleanAir);
    calcR0_S2 += S2.calibrate(RatioMQ8CleanAir);
    calcR0_S3 += S3.calibrate(RatioMQ135CleanAir);

    Serial.print(".");
    lcd.setCursor(i, 1);
    lcd.print(".");
  }
  S0.setR0(calcR0_S0 / 10);
  S1.setR0(calcR0_S1 / 10);
  S2.setR0(calcR0_S2 / 10);
  S3.setR0(calcR0_S3 / 10);
  Serial.println("  done!.");

  //    if (isinf(calcR0_S0)) {
  //      Serial.println("Warning: Conection issue founded, R0_S0 is infite (Open circuit detected) please check your wiring and supply");
  //      while (1);
  //    }
  //    if (calcR0_S0 == 0) {
  //      Serial.println("Warning: Conection issue founded, R0_S0 is zero (Analog pin with short circuit to ground) please check your wiring and supply");
  //      while (1);
  //    }
  //  if (isinf(calcR0_S1)) {
  //    Serial.println("Warning: Conection issue founded, R0_S1 is infite (Open circuit detected) please check your wiring and supply");
  //    while (1);
  //  }
  //  if (calcR0_S1 == 0) {
  //    Serial.println("Warning: Conection issue founded, R0_S1 is zero (Analog pin with short circuit to ground) please check your wiring and supply");
  //    while (1);
  //  }
  //  if (isinf(calcR0_S2)) {
  //    Serial.println("Warning: Conection issue founded, R0_S2 is infite (Open circuit detected) please check your wiring and supply");
  //    while (1);
  //  }
  //  if (calcR0_S2 == 0) {
  //    Serial.println("Warning: Conection issue founded, R0_S2 is zero (Analog pin with short circuit to ground) please check your wiring and supply");
  //    while (1);
  //  }
  //  if (isinf(calcR0_S3)) {
  //    Serial.println("Warning: Conection issue founded, R0_S3 is infite (Open circuit detected) please check your wiring and supply");
  //    while (1);
  //  }
  //  if (calcR0_S3 == 0) {
  //    Serial.println("Warning: Conection issue founded, R0_S3 is zero (Analog pin with short circuit to ground) please check your wiring and supply");
  //    while (1);
  //  }

  /*****************************  MQ CAlibration ********************************************/

  //  S0.serialDebug(true);
  //  S1.serialDebug(true);
  //  S2.serialDebug(true);
  //  S3.serialDebug(true);

}

void loop() {
  S0.update(); // Update data, the arduino will be read the voltage on the analog pin
  S1.update(); // Update data, the arduino will be read the voltage on the analog pin
  S2.update(); // Update data, the arduino will be read the voltage on the analog pin
  S3.update(); // Update data, the arduino will be read the voltage on the analog pin
  S0.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
  S1.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
  S2.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
  S3.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup



  //  float adc_S0, adc_S1, adc_S2, adc_S3;
  //  float volt_S0, volt_S1, volt_S2, volt_S3;
  //  float rs_S0, rs_S1, rs_S2, rs_S3;
  //  float ratio_S0, ratio_S1, ratio_S2, ratio_S3;
  float ppm_S0, ppm_S1, ppm_S2, ppm_S3;

  uint16_t r, g, b, c, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  //    colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  rn = map(r, 0, 1024, 0, 255);
  gn = map(g, 0, 1024, 0, 255);
  bn = map(b, 0, 1024, 0, 255);

  //  adc_S0 = S0.getadc();
  //  volt_S0 = S0.getvolt();
  //  rs_S0 = S0.getrs();
  //  ratio_S0 = S0.getratio();
  ppm_S0 = S0.getPPM();

  //  adc_S1 = S1.getadc();
  //  volt_S1 = S1.getvolt();
  //  rs_S1 = S1.getrs();
  //  ratio_S1 = S1.getratio();
  ppm_S1 = S1.getPPM();

  //  adc_S2 = S2.getadc();
  //  volt_S2 = S2.getvolt();
  //  rs_S2 = S2.getrs();
  //  ratio_S2 = S2.getratio();
  ppm_S2 = S2.getPPM();

  //  adc_S3 = S3.getadc();
  //  volt_S3 = S3.getvolt();
  //  rs_S3 = S3.getrs();
  //  ratio_S3 = S3.getratio();
  ppm_S3 = S3.getPPM();

  //
  //  //Assign collected data to JSON Object
  //  data["humidity"] = hum;
  //  data["temperature"] = temp;
  //
  //Send data to NodeMCU
  //  data.printTo(nodemcu);
  //  jsonBuffer.clear();


  Serial.print("S0: ");
  Serial.print(ppm_S0);
  Serial.print(" PPM\t");
  Serial.print("S1: ");
  Serial.print(ppm_S1);
  Serial.print(" PPM\t");
  Serial.print("S2: ");
  Serial.print(ppm_S2);
  Serial.print(" PPM\t");
  Serial.print("S3: ");
  Serial.print(ppm_S3);
  Serial.print(" PPM");

  Serial.print(" \t   Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(rn, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(gn, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(bn, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  Serial.println(" ");

  //Assign collected data to JSON Object

  //  int r = random(1,20);
  //  int g = random(1,20);
  //  int b = random(1,20);

  //    ppm_S0 = random(1, 20);
  //    ppm_S1 = random(1, 20);
  //    ppm_S2 = random(1, 20);
  //    ppm_S3 = random(1, 20);
  //
  //  StaticJsonBuffer<1000> jsonBuffer;
  //  JsonObject& data = jsonBuffer.createObject();
  //
  //  data["R"] = r;
  //  data["R"] = g;
  //  data["R"] = b;
  //  data["S0"] = ppm_S0;
  //  data["S1"] = ppm_S1;
  //  data["S2"] = ppm_S2;
  //  data["S3"] = ppm_S3;

  //Send data to NodeMCU
  //  data.printTo(nodemcu);
  //  jsonBuffer.clear();
  //  delay(2000);

  //Send data string to NODEMCU
  str = String(rn) + String(",") + String(gn) + String(",") + String(bn) + String(",") +
        String(ppm_S0) + String(",") + String(ppm_S1) + String(",") +
        String(ppm_S2) + String(",") + String(ppm_S3) + String(",");
  nodemcu.println(str);
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("S0:");
  lcd.print(ppm_S0);
  lcd.setCursor(8, 0);
  lcd.print("S1:");
  lcd.print(ppm_S1);
  lcd.setCursor(0, 1);
  lcd.print("S2:");
  lcd.print(ppm_S2);
  lcd.setCursor(8, 1);
  lcd.print("S3:");
  lcd.print(ppm_S3);


}
