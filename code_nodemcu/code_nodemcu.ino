#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

//Include Lib for Arduino to Nodemcu
#include <SoftwareSerial.h>
// Update these with values suitable for your network.

const char* ssid = "troll";
const char* password = "87654321";
const char* mqtt_server = "103.150.97.62";
//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);
WiFiClient espClient;V
PubSubClient client(espClient);
unsigned long lastMsg = 0;
//#define MSG_BUFFER_SIZE  (50)
//char msg[MSG_BUFFER_SIZE];
int value = 0;
float value1, value2, value3, value4, value5, value6, value7;
void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  //  nodemcu.begin(9600);
  //  while (!Serial) continue;
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
//    StaticJsonBuffer<1000> jsonReceived;
  //  JsonObject& ADUDU = jsonReceived.parseObject(nodemcu);

  //  int r = ADUDU["R"];
  //  int g = ADUDU["G"];
  //  int b = ADUDU["B"];
  //  int s0 = ADUDU["S0"];
  //  int s1 = ADUDU["S1"];
  //  int s2 = ADUDU["S2"];
  //  int s3 = ADUDU["S3"];

  //  int r = random(1,255);
  //  int g = random(1,255);
  //  int b = random(1,255);
  //  int s0 = random(1,1024);
  //  int s1 = random(1,1024);
  //  int s2 = random(1,1024);
  //  int s3 = random(1,1024);
  if (Serial.available()) {
    String dataString = Serial.readString();
    // Cetak data yang telah dibaca
    Serial.print("ini dari serial: ");
    Serial.println(dataString);

    parseMessage(dataString);
    // Cetak nilai-nilai yang telah di-parse
    Serial.println(value1);
    Serial.println(value2);
    Serial.println(value3);
    Serial.println(value4);
    Serial.println(value5);
    Serial.println(value6);
    Serial.println(value7);
  }
  StaticJsonBuffer<1000> jsonSend;
  JsonObject& MCU = jsonSend.createObject();
//  JSONencoder["device"] = "banana_ripeness";
  MCU["R"] = value1;
  MCU["G"] = value2;
  MCU["B"] = value3;
  MCU["S0"] = value4;
  MCU["S1"] = value5;
  MCU["S2"] = value6;
  MCU["S3"] = value7;

  //  JsonArray& rgb = JSONencoder.createNestedArray("ColorSensor");
  //  rgb.add(value1);
  //  rgb.add(value2);
  //  rgb.add(value3);
  //  JsonArray& values = JSONencoder.createNestedArray("MQSensor");
  //  values.add(value4);
  //  values.add(value5);
  //  values.add(value6);
  //  values.add(value7);



  char JSONmessageBuffer[100];
  MCU.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));


  unsigned long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    //    ++value;
    //    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.println("Sending message to MQTT topic..");
    Serial.println(JSONmessageBuffer);
    //    Serial.println(msg);
    client.publish("skripsi_faris19", JSONmessageBuffer);
  }
}

void parseMessage(String message) {
  // Lakukan parsing pesan di sini sesuai format pesan yang diinginkan
  // Contoh: Jika pesan berisi beberapa angka yang dipisahkan oleh koma (,),
  // dan ingin dipisah menjadi beberapa variabel float

  int commaIndex = 0;
  int dataIndex = 0;

  for (int i = 0; i < 7; i++) {
    commaIndex = message.indexOf(',', dataIndex);
    if (commaIndex != -1) {
      String valueStr = message.substring(dataIndex, commaIndex);
      valueStr.trim(); // Hapus karakter whitespace di awal dan akhir angka
      switch (i) {
        case 0: value1 = valueStr.toFloat(); break;
        case 1: value2 = valueStr.toFloat(); break;
        case 2: value3 = valueStr.toFloat(); break;
        case 3: value4 = valueStr.toFloat(); break;
        case 4: value5 = valueStr.toFloat(); break;
        case 5: value6 = valueStr.toFloat(); break;
        case 6: value7 = valueStr.toFloat(); break;
      }
      dataIndex = commaIndex + 1;
    }
  }
}
