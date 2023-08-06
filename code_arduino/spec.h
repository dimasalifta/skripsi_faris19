////Include the library
//#include <MQUnifiedsensor.h>
///************************Hardware Related Macros************************************/
//#define         Board                   ("Arduino UNO")
//#define         Pin                     (A2)  //Analog input 3 of your arduino
///***********************Software Related Macros************************************/
//#define         Type                    ("MQ-2") //MQ2
//#define         Voltage_Resolution      (5)
//#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO
//#define         RatioMQ2CleanAir        (9.83) //RS / R0 = 9.83 ppm 
//
///*****************************Globals***********************************************/
//MQUnifiedsensor MQ2(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
///*****************************Globals***********************************************/
//
//void setup() {
//  //Init the serial port communication - to debug the library
//  Serial.begin(9600); //Init serial port
//
//  //Set math model to calculate the PPM concentration and the value of constants
//  MQ2.setRegressionMethod(1); //_PPM =  a*ratio^b
//  MQ2.setA(574.25); MQ2.setB(-2.222); // Configurate the ecuation values to get LPG concentration
//  /*
//    Exponential regression:
//    Gas    | a      | b
//    H2     | 987.99 | -2.162
//    LPG    | 574.25 | -2.222
//    CO     | 36974  | -3.109
//    Alcohol| 3616.1 | -2.675
//    Propane| 658.71 | -2.168
//  */
//
//
//
//
//  / Include the library
//#include <MQUnifiedsensor.h>
//  /************************Hardware Related Macros************************************/
//#define         Board                   ("Arduino UNO")
//#define         Pin                     (A3)  //Analog input 3 of your arduino
//  /***********************Software Related Macros************************************/
//#define         Type                    ("MQ-3") //MQ3
//#define         Voltage_Resolution      (5)
//#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO
//#define         RatioMQ3CleanAir        (60) //RS / R0 = 60 ppm 
//  /*****************************Globals***********************************************/
//  //Declare Sensor
//  MQUnifiedsensor MQ3(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
//
//  void setup() {
//    //Init the serial port communication - to debug the library
//    Serial.begin(9600); //Init serial port
//
//    //Set math model to calculate the PPM concentration and the value of constants
//    MQ3.setRegressionMethod(1); //_PPM =  a*ratio^b
//    MQ3.setA(4.8387); MQ3.setB(-2.68); // Configurate the ecuation values to get Benzene concentration
//    /*
//      Exponential regression:
//      Gas    | a      | b
//      LPG    | 44771  | -3.245
//      CH4    | 2*10^31| 19.01
//      CO     | 521853 | -3.821
//      Alcohol| 0.3934 | -1.504
//      Benzene| 4.8387 | -2.68
//      Hexane | 7585.3 | -2.849
//    */
//
//
//    //Include the library
//#include <MQUnifiedsensor.h>
//    /************************Hardware Related Macros************************************/
//  #define         Board                   ("Arduino UNO")
//#define         Pin                     (A4)  //Analog input 4 of your arduino
//    /***********************Software Related Macros************************************/
//#define         Type                    ("MQ-4") //MQ4
//#define         Voltage_Resolution      (5)
//#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO
//#define         RatioMQ4CleanAir        (4.4) //RS / R0 = 60 ppm 
//    /*****************************Globals***********************************************/
//    //Declare Sensor
//    MQUnifiedsensor MQ4(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
//
//    void setup() {
//      //Init the serial port communication - to debug the library
//      Serial.begin(9600); //Init serial port
//
//      //Set math model to calculate the PPM concentration and the value of constants
//      MQ4.setRegressionMethod(1); //_PPM =  a*ratio^b
//      MQ4.setA(1012.7); MQ4.setB(-2.786); // Configurate the ecuation values to get CH4 concentration
//      /*
//        Exponential regression:
//        Gas    | a      | b
//        LPG    | 3811.9 | -3.113
//        CH4    | 1012.7 | -2.786
//        CO     | 200000000000000 | -19.05
//        Alcohol| 60000000000 | -14.01
//        smoke  | 30000000 | -8.308
//      */
//
//      / Definitions
//#define placa "Arduino UNO"
//#define Voltage_Resolution 5
//#define pin A0 //Analog input 0 of your arduino
//#define type "MQ-5" //MQ5
//#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
//#define RatioMQ5CleanAir 6.5  //RS / R0 = 6.5 ppm 
//      //#define calibration_button 13 //Pin to calibrate your sensor
//
//      //Declare Sensor
//      MQUnifiedsensor MQ5(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);
//
//      void setup() {
//        //Init the serial port communication - to debug the library
//        Serial.begin(9600); //Init serial port
//
//        //Set math model to calculate the PPM concentration and the value of constants
//        MQ5.setRegressionMethod(1); //_PPM =  a*ratio^b
//        MQ5.setA(1163.8); MQ5.setB(-3.874); // Configurate the ecuation values to get H2 concentration
//        /*
//          Exponential regression:
//          Gas    | a      | b
//          H2     | 1163.8 | -3.874
//          LPG    | 80.897 | -2.431
//          CH4    | 177.65 | -2.56
//          CO     | 491204 | -5.826
//          Alcohol| 97124  | -4.918
//        */
//
//
//        / Definitions
//#define placa "Arduino UNO"
//#define Voltage_Resolution 5
//#define pin A0 //Analog input 0 of your arduino
//#define type "MQ-6" //MQ6
//#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
//#define RatioMQ6CleanAir 10   //RS / R0 = 10 ppm 
//        //#define calibration_button 13 //Pin to calibrate your sensor
//
//        //Declare Sensor
//        MQUnifiedsensor MQ6(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);
//
//        void setup() {
//          //Init the serial port communication - to debug the library
//          Serial.begin(9600); //Init serial port
//
//          //Set math model to calculate the PPM concentration and the value of constants
//          MQ6.setRegressionMethod(1); //_PPM =  a*ratio^b
//          MQ6.setA(2127.2); MQ6.setB(-2.526); // Configurate the ecuation values to get CH4 concentration
//          /*
//            Exponential regression:
//            GAS     | a      | b
//            H2      | 88158  | -3.597
//            LPG     | 1009.2 | -2.35
//            CH4     | 2127.2 | -2.526
//            CO      | 1000000000000000 | -13.5
//            Alcohol | 50000000 | -6.017
//          */
//
//
//          //Include the library
//#include <MQUnifiedsensor.h>
//
//          //Definitions
//#define placa "Arduino UNO"
//#define Voltage_Resolution 5
//#define pin A0 //Analog input 0 of your arduino
//#define type "MQ-7" //MQ7
//#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
//#define RatioMQ7CleanAir 27.5 //RS / R0 = 27.5 ppm 
//          //#define calibration_button 13 //Pin to calibrate your sensor
//
//          //Declare Sensor
//          MQUnifiedsensor MQ7(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);
//
//          void setup() {
//            //Init the serial port communication - to debug the library
//            Serial.begin(9600); //Init serial port
//
//            //Set math model to calculate the PPM concentration and the value of constants
//            MQ7.setRegressionMethod(1); //_PPM =  a*ratio^b
//            MQ7.setA(99.042); MQ7.setB(-1.518); // Configurate the ecuation values to get CO concentration
//
//            /*
//              Exponential regression:
//              GAS     | a      | b
//              H2      | 69.014  | -1.374
//              LPG     | 700000000 | -7.703
//              CH4     | 60000000000000 | -10.54
//              CO      | 99.042 | -1.518
//              Alcohol | 40000000000000000 | -12.35
//            */
//
//            / Include the library
//#include <MQUnifiedsensor.h>
//
//            //Definitions
//#define placa "Arduino UNO"
//#define Voltage_Resolution 5
//#define pin A0 //Analog input 0 of your arduino
//#define type "MQ-8" //MQ8
//#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
//#define RatioMQ8CleanAir 70   //RS / R0 = 70 ppm  
//            //#define calibration_button 13 //Pin to calibrate your sensor
//
//            //Declare Sensor
//            MQUnifiedsensor MQ8(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);
//
//            void setup() {
//              //Init the serial port communication - to debug the library
//              Serial.begin(9600); //Init serial port
//
//              //Set math model to calculate the PPM concentration and the value of constants
//              MQ8.setRegressionMethod(1); //_PPM =  a*ratio^b
//              MQ8.setA(976.97); MQ8.setB(-0.688); // Configurate the ecuation values to get H2 concentration
//
//              /*
//                Exponential regression:
//                GAS     | a      | b
//                H2      | 976.97  | -0.688
//                LPG     | 10000000 | -3.123
//                CH4     | 80000000000000 | -6.666
//                CO      | 2000000000000000000 | -8.074
//                Alcohol | 76101 | -1.86
//              */
//
//
//              //Include the library
//#include <MQUnifiedsensor.h>
//              /************************Hardware Related Macros************************************/
//#define         Board                   ("Arduino UNO")
//#define         Pin                     (A9)  //Analog input 4 of your arduino
//              /***********************Software Related Macros************************************/
//#define         Type                    ("MQ-9") //MQ9
//#define         Voltage_Resolution      (5)
//#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO
//#define         RatioMQ9CleanAir        (9.6) //RS / R0 = 60 ppm 
//              /*****************************Globals***********************************************/
//              //Declare Sensor
//              MQUnifiedsensor MQ9(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
//
//              void setup() {
//                //Init the serial port communication - to debug the library
//                Serial.begin(9600); //Init serial port
//
//                //Set math model to calculate the PPM concentration and the value of constants
//                MQ9.setRegressionMethod(1); //_PPM =  a*ratio^b
//                MQ9.setA(1000.5); MQ9.setB(-2.186); // Configurate the ecuation values to get LPG concentration
//
//                /*
//                  Exponential regression:
//                  GAS     | a      | b
//                  LPG     | 1000.5 | -2.186
//                  CH4     | 4269.6 | -2.648
//                  CO      | 599.65 | -2.244
//                */
//
//                //Include the library
//#include <MQUnifiedsensor.h>
//
//                //Definitions
//#define placa "Arduino UNO"
//#define Voltage_Resolution 5
//#define pin A0 //Analog input 0 of your arduino
//#define type "MQ-135" //MQ135
//#define ADC_Bit_Resolution 10 // For arduino UNO/MEGA/NANO
//#define RatioMQ135CleanAir 3.6//RS / R0 = 3.6 ppm  
//                //#define calibration_button 13 //Pin to calibrate your sensor
//
//                //Declare Sensor
//                MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);
//
//                void setup() {
//                  //Init the serial port communication - to debug the library
//                  Serial.begin(9600); //Init serial port
//
//                  //Set math model to calculate the PPM concentration and the value of constants
//                  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
//                  MQ135.setA(102.2); MQ135.setB(-2.473); // Configurate the ecuation values to get NH4 concentration
//
//                  /*
//                    Exponential regression:
//                    GAS      | a      | b
//                    CO       | 605.18 | -3.937
//                    Alcohol  | 77.255 | -3.18
//                    CO2      | 110.47 | -2.862
//                    Tolueno  | 44.947 | -3.445
//                    NH4      | 102.2  | -2.473
//                    Acetona  | 34.668 | -3.369
//                  */
