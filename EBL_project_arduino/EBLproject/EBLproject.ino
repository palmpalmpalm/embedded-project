#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

Servo myservo;

float val;
char cond;
bool xstart = true;
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
SoftwareSerial NodeSerial(13,15); //rx||tx

#define FIREBASE_HOST "embededlab-aa618-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "zFyMe30TlRpAP35DUc7klEMz4yzh7CkxEcUgkyFx"
#define WIFI_SSID "Boat.2G"
#define WIFI_PASSWORD "024181779"
 
void setup() {

myservo.attach(16);
mlx.begin();
pinMode(13, INPUT); 
pinMode(15, OUTPUT);

Serial.begin(9600);
NodeSerial.begin(9600);
//Serial.println("Adafruit MLX90614 test");

// connect to wifi.
  delay(500);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  delay(500);
  Serial.print("connecting");
  delay(500);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


 
void loop() {
  if(!xstart){
    Serial.print("Ambient = ");
    Serial.print(mlx.readAmbientTempC());
    Serial.print("*C\tObject = ");
    Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  }
  if(xstart){
    while(mlx.readAmbientTempC()>1000){
      Serial.print("Ambient = ");
      Serial.print(mlx.readAmbientTempC());
      Serial.print("*C\tObject = ");
      Serial.print(mlx.readObjectTempC()); Serial.println("*C");
      val = mlx.readObjectTempC();
      delay(100);
    }
      Serial.println("=====");
  
    //POST_people
    // set value
    Firebase.setInt("/people", 0);
    // handle error
    if (Firebase.failed()) {
        Serial.print("setting /people failed:");
        Serial.println(Firebase.error());  
        return;
    }
    delay(1000);
    
    //POST_Temp
    // set value
    Firebase.setFloat("/Temp", 0.0);
    // handle error
    if (Firebase.failed()) {
        Serial.print("setting /Temp failed:");
        Serial.println(Firebase.error());  
        return;
    }
    delay(1000);
    
    //POST_Door_status
    // set value
    Firebase.setInt("/Door_status", 0);
    // handle error
    if (Firebase.failed()) {
        Serial.print("setting /Door_status failed:");
        Serial.println(Firebase.error());  
        return;
    }
  }
  
  //Serial.println(cond);
  while(NodeSerial.available()>0) {
    cond = NodeSerial.read();
    Serial.println(cond);
  }
  
  if(cond == 'i'){
    NodeSerial.print('u');
//    Serial.print("Ambient = ");
//    Serial.print(mlx.readAmbientTempC());
    Serial.print("Object = ");
    Serial.print(mlx.readObjectTempC()); Serial.println("*C");
    val = mlx.readObjectTempC();

    //UPDATE_Temp
    // update value
    Firebase.setFloat("/Temp", val);
    // handle error
    if (Firebase.failed()) {
        Serial.print("setting /Temp failed:");
        Serial.println(Firebase.error());  
        return;
    }
    delay(1000);
    
    if(val < 30.5){
      
      myservo.write(180); // สั่งให้ Servo หมุนวนขวา
      //UPDATE_Door_status
      // update value
      Firebase.setFloat("/Door_status", 1);
      // handle error
      if (Firebase.failed()) {
          Serial.print("setting /Door_status failed:");
          Serial.println(Firebase.error());  
          return;
      }
      delay(1000);
      
      //GET
      // get value 
      Serial.print("people: ");
      int count = Firebase.getInt("/people");
      Serial.println(count+1);
      delay(1000);
      
      
      //UPDATE_people
      // update value
      Firebase.setFloat("/people", count+1);
      // handle error
      if (Firebase.failed()) {
          Serial.print("setting /people failed:");
          Serial.println(Firebase.error());  
          return;
      }
      delay(2000);
      
      myservo.write(0); // สั่งให้ Servo หมุนวนขวาซ้าย
      //UPDATE_Door_status
      // update value
      Firebase.setFloat("/Door_status", 0);
      // handle error
      if (Firebase.failed()) {
          Serial.print("setting /Door_status failed:");
          Serial.println(Firebase.error());  
          return;
      }
      delay(1000);

      
    }
    else {
      //UPDATE_Door_status
      // update value
      Firebase.setFloat("/Door_status", 2);
      // handle error
      if (Firebase.failed()) {
          Serial.print("setting /Door_status failed:");
          Serial.println(Firebase.error());  
          return;
      }
      delay(3000);

      //UPDATE_Door_status
      // update value
      Firebase.setFloat("/Door_status", 0);
      // handle error
      if (Firebase.failed()) {
          Serial.print("setting /Door_status failed:");
          Serial.println(Firebase.error());  
          return;
      }
      delay(1000);
    }
    
    
  }  
  if(cond == 'o'){
    NodeSerial.print('u');
    //GET
    // get value 
    Serial.print("people: ");
    int count = Firebase.getInt("/people");
    Serial.println(count+1);
    delay(1000);
    
    //UPDATE_people
    // update value
    Firebase.setFloat("/people", count-1);
    // handle error
    if (Firebase.failed()) {
        Serial.print("setting /people failed:");
        Serial.println(Firebase.error());  
        return;
    }
    delay(1000);
  }
  NodeSerial.print('d');
  delay(500);
  xstart = false;
  cond = 'a';

}
