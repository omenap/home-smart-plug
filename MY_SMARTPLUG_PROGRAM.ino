#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <ESP8266WebServer.h>
ESP8266WebServer webserver(80);

#define FIREBASE_HOST "smartdevice-c8bcb-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "k1UzmwrySld4KxfTYSZ7mpr4he1xq71HxsYOBOZk"
#define WIFI_SSID "8pxX2"
#define WIFI_PASSWORD "coldmineral"
int relay1 = 5;
int relay2 = 4;
int led = 13;
int led2 = 12;
String state;
FirebaseData firebaseData;
FirebaseData loadData;
void setup() {
  Serial.begin(115200);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(led2,OUTPUT);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() !=WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println("Connected");
}
void loop() {
 if(Firebase.getString(loadData,"/smartDB/load")){
    if(loadData.stringData()== "1"){
      digitalWrite(relay1,HIGH);
      digitalWrite(relay2,HIGH);
      digitalWrite(led,HIGH);
      digitalWrite(led2,HIGH);
      Serial.println("ON");
      state="ON";
      }
        else{
    if(loadData.stringData()== "0"){
      digitalWrite(relay1,LOW);
      digitalWrite(relay2,LOW);
      digitalWrite(led,LOW);
      digitalWrite(led2,LOW);
      Serial.println("OFF");
      state="OFF";
      }
    }
  } 
}

