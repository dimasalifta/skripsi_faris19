#define BLYNK_PRINT Serial

#include <MQUnifiedsensor.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiClient.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

WiFiClient client;

#define led_merah D6
#define led_hijau D5
#define relay D3

#define DHTPIN D7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);
/* Comment this out to disable prints and save space */

// Input token project ke Blynk App.
char auth[] = "H27fPcL09dPnO65uKWApLteCIudxrvBA";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Hasbi";
char pass[] = "bjla3888";

//Thingspeak
String apiKey = "M9SZNELFBXD9EKGF";
const char* server = "api.thingspeak.com";

//Definitions
#define placa ("ESP8266")
#define Voltage_Resolution 5
#define pin A0 //Analog input 0 of your arduino
#define type "MQ-135" //MQ135
#define ADC_Bit_Resolution 10
#define RatioMQ135CleanAir 3.6//RS / R0 = 3.6 ppm  
//#define calibration_button 13 //Pin to calibrate your sensor

//Declare Sensor
MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

float Amonia, Humidity;
float A, B;
float uNormal[] = {0, 0, 20, 30};
float uSedang[] = {20, 30, 50, 60};
float uTinggi[] = {50, 60, 80, 80};
float uKering[] = {0, 0, 25, 45};
float uLembab[] = {25, 45, 65, 85};
float uBasah[] = {65, 85, 100, 100};
float Aman = 0;
float Waspada = 0.5;
float Bahaya = 1;
float minr[10];
float Rule[10];

float fuNormal()
{
  if (Amonia < uNormal[1])
  {
    return 1;
  }
  else if (Amonia >= uNormal[1] && Amonia <= uNormal[2])
  {
    return (uNormal[2] - Amonia) / (uNormal[2] - uNormal[1]);
  }
  else if (Amonia > uNormal[2])
  {
    return 0;
  }
}
float fuSedang()
{
  if (Amonia <= uSedang[0])
  {
    return 0;
  }
else if (Amonia >= uSedang[0] && Amonia <= uSedang[1])
  {
    return (Amonia - uSedang[0]) / (uSedang[1] - uSedang[0]);
  }
  else if (Amonia > uSedang[1] && Amonia <= uSedang[2])
  {
    return 1;
  }
  else if (Amonia > uSedang[3])
  {
    return (uSedang[3] - Amonia) / (uSedang[3] - uSedang[2]) ;
  }
}
float fuTinggi()
{
  if (Amonia <= uTinggi[0])
  {
    return 0;
  }
  else if (Amonia >= uTinggi[0] && Amonia <= uTinggi[1])
  {
    return (Amonia - uTinggi[0]) / (uTinggi[1] - uTinggi[0]);
  }
  else if (Amonia > uTinggi[1])
  {
    return 1;
  }
}
float fuKering()
{
  if (Humidity < uKering[1])
  {
    return 1;
  }
  else if (Humidity >= uKering[1] && Humidity <= uKering[2])
  {
    return (uKering[2] - Humidity) / (uKering[2] - uKering[1]);
  }
  else if (Humidity > uKering[2])
  {
    return 0;
  }
}
float fuLembab()
{
  if (Humidity <= uLembab[0])
  {
    return 0;
  }
  else if (Humidity >= uLembab[0] && Humidity <= uLembab[1])
  {
    return (Humidity - uLembab[0]) / (uLembab[1] - uLembab[0]);
  }
  else if (Humidity >= uLembab[1] && Humidity <= uLembab[2])
  {
    return 1;
  }
  else if (Humidity > uLembab[3])
  {
    return (uLembab[3] - Humidity) / (uLembab[3] - uLembab[2]);
  }
}
float fuBasah()
{
  if (Humidity <= uBasah[0])
  {
    return 0;
  }
  else if (Humidity >= uBasah[0] && Humidity <= uBasah[1])
  {
    return (Humidity - uBasah[0]) / (uBasah[1] - uBasah[0]);
  }
  else if (Humidity > uBasah[1])
  {
    return 1;
  }
}
float Min(float a, float b)
{
  if (a < b)
  {
    return a;
  }
  else if (b < a)
  {
    return b;
  }
  else
  {
    return a;
  }
}
void rule()
{
  //if Amonia Normal and Humidity Kering then Aman
  minr[1] = Min(fuNormal(), fuKering());
  Rule[1] = Aman;
  //if Amonia Normal and Humidity Lembab then Aman
  minr[2] = Min(fuNormal(), fuLembab());
  Rule[2] = Aman;
  // if Amonia Sedang and Humidity Kering then Aman
  minr[3] = Min(fuSedang(), fuKering());
  Rule[3] = Aman;
  //if Amonia Normal and Humidity Basah then Waspada
  minr[4] = Min(fuNormal(), fuBasah());
  Rule[4] = Waspada;
  // if Amonia Sedang and Humidity Lembab then Waspada
  minr[5] = Min(fuSedang(), fuLembab());
  Rule[5] = Waspada;
  // if Amonia Tinggi and Humidity Kering then Waspada
  minr[6] = Min(fuTinggi(), fuKering());
  Rule[6] = Waspada;
  // if Amonia Sedang and Humidity Basah then Bahaya
  minr[7] = Min(fuSedang(), fuBasah());
  Rule[7] = Bahaya;
  // if Amonia Tinggi and Humidity Lembab then Bahaya
  minr[8] = Min(fuTinggi(), fuLembab());
  Rule[8] = Bahaya;
  //if Amonia Tinggi and Humidity Lembab then Bahaya
  minr[9] = Min(fuTinggi(), fuLembab());
  Rule[9] = Bahaya;
}

float defuzzyfikasi()
{
  rule();
  A = 0;
  B = 0;
  for (int i = 1; i <= 9; i++)
  {
    printf("Rule ke %d = %f\n", i, Rule[i]);
    printf("Min ke %d = %f\n", i, minr[i]);
    A += Rule[i] * minr[i];
    B += minr[i];
  }
  printf("Hasil A : %f\n", A);
  printf("Hasil B : %f\n", B);
  return A / B;
}

void setup()
{
  // Debug console
  Wire.begin();
  Serial.begin(115200);

  //  LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Welcome To");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring NH3");
  Serial.print("Setup LCD......");
  Serial.println("DONE");


  Serial.print("Setup LED dan Relay......");
  pinMode(led_merah, OUTPUT);
  pinMode(led_hijau, OUTPUT);
  pinMode(relay, OUTPUT);
  Serial.println("DONE");

  Serial.print("Setup Blynk......");
  Blynk.begin(auth, ssid, pass);
  Serial.println("DONE");

  Serial.print("Setup DHT......");
  dht.begin();
  Serial.println("DONE");


  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.setA(102.2); MQ135.setB(-2.473); // Configurate the ecuation values to get NH4 concentration

  /*
    Exponential regression:
    GAS      | a      | b
    CO       | 605.18 | -3.937
    Alcohol  | 77.255 | -3.18
    CO2      | 110.47 | -2.862
    Tolueno  | 44.947 | -3.445
    NH4      | 102.2  | -2.473
    Acetona  | 34.668 | -3.369
  */

  /**  MQ Init ***/
  //Remarks: Configure the pin of arduino as input.
  /****/
  MQ135.init();
  Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for (int i = 1; i <= 10; i ++)
  {
    MQ135.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    Serial.print(".");
  }
  MQ135.setR0(calcR0 / 10);
  Serial.println("  done!.");

  if (isinf(calcR0)) {
    Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your wiring and supply");
    while (1);
  }
  if (calcR0 == 0) {
    Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply");
    while (1);
  }
  /**  MQ CAlibration ***/
  MQ135.serialDebug(false);


}

void loop()
{
  Blynk.run();
  MQ135.update(); // Update data, the arduino will be read the voltage on the analog pin
  MQ135.readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
  // MQ135.serialDebug(); // Will print the table on the serial port

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float adc, volt, rs, ratio, ppm;
  adc = MQ135.getadc();
  volt = MQ135.getvolt();
  rs = MQ135.getrs();
  ratio = MQ135.getratio();
  ppm = MQ135.getppm();

  //Menghubungkan keluaran dengan Blynk App
  Blynk.virtualWrite(V0, adc);
  Blynk.virtualWrite(V1, volt);
  Blynk.virtualWrite(V2, rs);
  Blynk.virtualWrite(V3, ratio);
  Blynk.virtualWrite(V4, ppm); //Gas amonia
  Blynk.virtualWrite(V5, t); //Suhu
  Blynk.virtualWrite(V6, h); //Kelembaban

  delay(500); //Sampling frequency

  //LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEMP(C) | HUM(%)");
  lcd.setCursor(1, 1);
  lcd.print(t);
  lcd.setCursor(10, 1);
  lcd.print(h);
  delay(500);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("NH3 (ppm)");
  lcd.setCursor(1, 1);
  lcd.print(ppm);
  delay (500);
  //  lcd.clear();

  //Kirim data ke thingspeak
  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "&field3=";
    postStr += String(ppm);
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print("C, Humidity: ");
    Serial.print(h);
    Serial.print("%, NH3: ");
    Serial.print(ppm);
    Serial.println("ppm. Send to Thingspeak.");
  }
  client.stop();

  if (ppm >= 21) {
    digitalWrite(led_merah, HIGH); //turn LED red ON (Danger & exchaust fan ON)
    digitalWrite(led_hijau, LOW); //turn LED red ON (Danger & exchaust fan ON)
    digitalWrite(relay, HIGH);
  }
  else if (ppm <= 20) {
    digitalWrite(led_merah, LOW);
    digitalWrite(led_hijau, HIGH); //turn LED red ON (Danger & exchaust fan ON)
    digitalWrite(relay, LOW);
  }


//Amonia = ppm;
//Humidity = h;
float keputusan = defuzzyfikasi();
String msg;
Serial.print("Hasil Keputusan Defuzzyfikasi : ");
Serial.print("Status : ");
Serial.println(keputusan);

//if (keputusan == 0) {
//  digitalWrite(led_hijau, HIGH);
//  digitalWrite(led_merah, LOW);
//  digitalWrite(relay, LOW);
//  msg = "Aman";
//} else if (keputusan == 0.5) {
//  msg = "Waspada";
//  digitalWrite(led_merah, HIGH); //turn LED red ON (Danger & exchaust fan ON)
//  digitalWrite(led_hijau, LOW);
//  digitalWrite(relay, HIGH);
//} else if (keputusan == 1) {
//  digitalWrite(led_merah, HIGH); //turn LED red ON (Danger & exchaust fan ON)
//  digitalWrite(led_hijau, LOW);
//  digitalWrite(relay, HIGH);
//  msg = "Bahaya !!!";
//}
//Serial.println(msg);
}
