#include<ESP8266WiFi.h>
String ssid="ZAHIR-AHMED-MALIK";
String pass="1230ABA4";
String server="api.thingspeak.com";
WiFiClient client;

#include<DHT.h>
#define DHTTYPE DHT11
#define DHTPIN D5

DHT dht(DHTPIN,DHTTYPE);

void setup() {
  // put your setup code here, to run once:

dht.begin();
Serial.begin(9600);
pinMode(D1,INPUT);  //BUTTON 1
pinMode(D2,INPUT);  //BUTTON 2
pinMode(D3,INPUT); //BUTTON 3
pinMode(A0,INPUT);  //TO DETECT STEAM VALUE
pinMode(D5,INPUT);  //TO CONNECT TO RELAY MODULE
pinMode(D6,OUTPUT);  // BUZZER
pinMode(D4,OUTPUT); //TO DETECT TEMPERATURE AND HUMIDITY
digitalWrite(D4,HIGH); //LIGHT OFF

 WiFi.begin(ssid,pass);
  Serial.print("connecting..");
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("wifi connected");
  Serial.println(WiFi.localIP());
  
}

void loop() {
  float temp=dht.readTemperature();
  int a=digitalRead(D1);
  int b=digitalRead(D2);
  int c=digitalRead(D3);
 
  if(a==HIGH){
    int x=analogRead(A0);
    Serial.println("GAS VALUE IS ");
    Serial.println(x);
    delay(1000);
    if(x>=720){
      digitalWrite(D6,HIGH);
    }
    else
     digitalWrite(D6,LOW);
  }
   if(c==HIGH){
      float humidity=dht.readHumidity();
      Serial.println("HUMIDITY IS");
      Serial.println(humidity);
      delay(1000);
      }
  if(b==HIGH){
      Serial.println("TEMPERATURE IS");
      Serial.println(temp);
      delay(1000);
      if(temp>=26.40){
       digitalWrite(D4,LOW);
      }
      else{
       digitalWrite(D4,HIGH);    
      }
      }
      
     float humidity=dht.readHumidity();
     int x=analogRead(A0);
    
     if(client.connect(server,80)){
     client.println("GET /update?api_key=FCI1WEA9H0FPM4OE&field1=0="+String(temp)+"&field2="+String(humidity)+"&field3="+String(x)+" HTTP/1.0");
     client.println();
     }
     client.stop(); 
  }
  

 
