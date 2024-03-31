#define S1 13       
#define S2 12      
#define ENA 16
#define IN_1  5        
#define IN_2  4       
#define IN_3  0        
#define IN_4  2        
#define ENB   14


#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;
String a="1";

const char* ssid = "doracake";
const char* password = "12345678";
ESP8266WebServer server(80);

void setup() {
 
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
 pinMode(S2, INPUT);
 pinMode(S1, INPUT); 

  Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void goLeft(){
digitalWrite(IN_1, LOW);
digitalWrite(IN_2, HIGH);
analogWrite(ENA, speedCar);
digitalWrite(IN_3, LOW);
digitalWrite(IN_4, HIGH);
analogWrite(ENB, speedCar);
}
void goRight(){
digitalWrite(IN_1, HIGH);
digitalWrite(IN_2, LOW);
analogWrite(ENA, speedCar);
digitalWrite(IN_3, HIGH);
digitalWrite(IN_4, LOW);
analogWrite(ENB, speedCar);
}
void goBack(){
digitalWrite(IN_1, HIGH);
digitalWrite(IN_2, LOW);
analogWrite(ENA, speedCar);
digitalWrite(IN_3, LOW);
digitalWrite(IN_4, HIGH);
analogWrite(ENB, speedCar);
}
void goAhead(){
digitalWrite(IN_1, LOW);
digitalWrite(IN_2, HIGH);
analogWrite(ENA, speedCar);
digitalWrite(IN_3, HIGH);
digitalWrite(IN_4, LOW);
analogWrite(ENB, speedCar);
}
void goAheadRight(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar/speed_Coeff);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
   }

void goAheadLeft(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void goBackRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar/speed_Coeff);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goBackLeft(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
 }

void loop() {
    server.handleClient();
    if(server.arg("State")){
      command = server.arg("State");
      a=command;
      }
      
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023;
      else if (command == "S") stopRobot();


      else if(a == "0"){
        speedCar = 540;
        if(digitalRead(S1)==LOW  && digitalRead(S2)==LOW)
      {
        goAhead();
      }
      if(digitalRead(S1)==HIGH  && digitalRead(S2)==LOW)
      {
        goRight();
      }
      if(digitalRead(S1)==LOW  && digitalRead(S2)==HIGH)
      {
        goLeft();
      }
      if(digitalRead(S1)==HIGH  && digitalRead(S2)==HIGH)
      {
        stopRobot();
      }
    }
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}