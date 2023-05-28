#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "homepage.h"

Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);

const char* ssid = "Jennings Wifi";
const char* password = "UnevenSea455";
WebServer server(80);

const int LED = 19; 
const int PushButton = 15;
const int Lock = 32;
const int Servo = 27;
const int Buzzer = 18;
const int FaceID = 4;
int pos = 0;
bool unlock = false;
bool safeAccess = true;
bool noAccess = false;

void IRAM_ATTR isr(){
  if(safeAccess == false){
    noAccess = true;
  }
  else{
    unlock = true;
  } 
}


void handleRoot() {
  String message = "";
  if(safeAccess == false){
    message = homepageLock;
  }
  else{
    message = homepageUnlock;
  }
  server.send(200, "text/html", message);  
}

void handleKeyPress(){
  String keyPress = server.arg("button");
  char button = keyPress.charAt(0);
  switch(button){
    case 'L':
    Serial.println("Safe is no longer unlockable");
    safeAccess = false;
    break;
    case 'U':
    Serial.println("Safe is now unlockable");
    safeAccess = true;
    break;
    }
  server.send(200);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup() {
  Serial.begin(115200);

  myservo.attach(Servo, 550, 2400);
  pos = 88;
  myservo.write(pos);               
  
  pinMode(LED, OUTPUT);
  pinMode(PushButton, INPUT);
  pinMode(FaceID, INPUT);
  pinMode(Lock, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(Lock, LOW);
  digitalWrite(Buzzer, LOW);

  lcd.init();
  lcd.clear();  
  lcd.print("Safe Locked");

  attachInterrupt(FaceID, isr, RISING);	 

  // Connect to Wi-Fi network with SSID and password
  //Wifi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/sentKeyPressToWebServer", handleKeyPress);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  delay(2);

  if(unlock == true){ 
    UNLOCK();
    delay(5000);
    unlock = false;
  } 
  if(noAccess == true){
    AccessDisabled();
    noAccess = false;
  }
}

void UNLOCK(){
    //Safe Unlocked
    digitalWrite(LED, HIGH); 
    digitalWrite(Lock, HIGH);
    lcd.clear();  
    lcd.setCursor(0,0); 
    lcd.print("Safe Unlocked");
    lcd.setCursor(0,1);
    lcd.print("Door Opening");
    delay(1000);
    digitalWrite(Buzzer, HIGH);
    
    //Slowly opens safe door
    for (pos = 88; pos >= 0; pos--){ 
		  myservo.write(pos);    
	  	delay(20);             
	  }
    digitalWrite(Buzzer, LOW);
    
    lcd.clear();  
    lcd.setCursor(0,0); 
    lcd.print("Press Button");
    lcd.setCursor(0,1);
    lcd.print("When Finished"); 
    while(digitalRead(PushButton) == LOW){}

    lcd.clear();   
    lcd.print("Door Closing...");
    digitalWrite(Buzzer, HIGH);

    //Slowly closes safe door
    for (pos = 0; pos <= 88; pos++){
	  	myservo.write(pos);    
	  	delay(20);             
  	}
    digitalWrite(Buzzer, LOW);

    lcd.clear();   
    lcd.print("Door Closed");
    delay(2000);
    digitalWrite(LED, LOW);
    digitalWrite(Lock, LOW);
    lcd.clear();  
    lcd.print("Safe Locked");   
}

void AccessDisabled(){
    lcd.clear();
    lcd.setCursor(0,0);  
    lcd.print("Safe access has");
    lcd.setCursor(0,1);
    lcd.print("been disabled");
    delay(3000);
    lcd.clear();
    lcd.print("Safe Locked");
}