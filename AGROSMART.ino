//;
'{#include <ArduinoRobotMotorBoard.h>
//#include <EasyTransfer2.h>
//#include <LineFollow.h>
//#include <Multiplexer.h>
//
//#include <ArduinoRobot.h>
//#include <Arduino_LCD.h>
//#include <Compass.h>
//#include <EasyTransfer2.h>
//#include <EEPROM_I2C.h>
//#include <Fat16.h>
//#include <Fat16Config.h>
//#include <Fat16mainpage.h>
//#include <Fat16util.h>
//#include <FatStructs.h>
//#include <Multiplexer.h>
//#include <SdCard.h>
//#include <SdInfo.h>
//#include <Squawk.h>
//#include <SquawkSD.h>

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */

#define BLYNK_TEMPLATE_ID "TMPLESx1lbod"
#define BLYNK_DEVICE_NAME "Agribot"
#define BLYNK_AUTH_TOKEN "06-rjIsqpdw0JldjcamJ6EHPJKljTodG"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


#define DHTPIN D4
#define DHTTYPE DHT11
#include<DHT.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).



// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ninja";
char pass[] = "dingding";
char auth[] = BLYNK_AUTH_TOKEN;


int m1Clock=D8;
int m1AntiClock=D7;
int m2Clock=D6;
int m2AntiClock=D5;
int m3=D1;
int pump_pin=D0;
int moisture_pin=D3;
DHT dht(DHTPIN , DHTTYPE);

void setup()
{
  
  // Debug console
  Serial.begin(9600);
  pinMode(m1Clock,OUTPUT);
  pinMode(m1AntiClock,OUTPUT);
  pinMode(m2Clock,OUTPUT);
  pinMode(m2AntiClock,OUTPUT);
  pinMode(m3,OUTPUT);
    
  pinMode(pump_pin,OUTPUT);
  pinMode(moisture_pin,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
   dht.begin();
}

void loop()
{
  Blynk.run();
  moisture_status();
  Blynk.virtualWrite(V2, dht.readHumidity());
  //dht Temperature
  Blynk.virtualWrite(V1, dht.readTemperature());
}

BLYNK_WRITE(V3){
  int val=param.asInt();
  if(val){
    Blynk.virtualWrite(V9,"Forward Start");
    digitalWrite(m1Clock,HIGH);
    digitalWrite(m2Clock,HIGH);
  }else{
    Blynk.virtualWrite(V9,"Forward stop");
    digitalWrite(m1Clock,LOW);
    digitalWrite(m2Clock,LOW);
  }
}

BLYNK_WRITE(V4){
  int val=param.asInt();
  if(val){
    digitalWrite(m1AntiClock,HIGH);
    digitalWrite(m2AntiClock,HIGH);
    Blynk.virtualWrite(V9,"Backward Start");
  }else{
    digitalWrite(m1AntiClock,LOW);
    digitalWrite(m2AntiClock,LOW);
    Blynk.virtualWrite(V9,"Backward stop");
  }
}

BLYNK_WRITE(V5){
  int val=param.asInt();
  if(val){
    digitalWrite(m1Clock,HIGH);
    digitalWrite(m2Clock,LOW);
    Blynk.virtualWrite(V9,"Left Start");
  }else{
    digitalWrite(m1Clock,LOW);

    Blynk.virtualWrite(V9,"Left stop");
  }
}

BLYNK_WRITE(V6){
  int val=param.asInt();
  if(val){
    digitalWrite(m1Clock,LOW);
    digitalWrite(m2Clock,HIGH);
    Blynk.virtualWrite(V9,"Right Start");
  }else{
    digitalWrite(m2Clock,LOW);
    
    Blynk.virtualWrite(V9,"Right stop");
  }
}

BLYNK_WRITE(V8){
  int val=param.asInt();
  if(val){
    digitalWrite(m3,HIGH);
    Blynk.virtualWrite(V9,"Harvesting");
  }else{
    digitalWrite(m3,LOW);
    Blynk.virtualWrite(V9,"........");
  }
}

//Water Pump
BLYNK_WRITE(V7){
  int val=param.asInt();
  if(val){
    digitalWrite(pump_pin,HIGH);
    Blynk.virtualWrite(V9,"On");
  }else{
    digitalWrite(pump_pin,LOW);
    Blynk.virtualWrite(V9,".....");
  }
}
void moisture_status(){
  if(digitalRead(moisture_pin)){
    Blynk.virtualWrite(V0, ".........");
  }else{
    Blynk.virtualWrite(V0, "Moisture Present");
  }
}
