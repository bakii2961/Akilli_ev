#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

int perde1 = 0,perde2 = 0,perde3 = 0,led1 = 0,led2 = 0,led3 = 0,gaz_output,guc_output;
const char* ssid = "Galaxy A04 5430";
const char* password = "Musa4646";
const char* mqtt_server = "192.168.40.218";
const int ledPin1 = D4; // İlk LED pin numarası
const int ledPin2 = D5; // İkinci LED pin numarası
const int ledPin3 = D6; // Üçüncü LED pin numarası

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3;
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
  String konu = String((char*)topic);
  if (konu == "Perde1") {
        String input = "";
    for (int i = 0; i < length; i++)
    {
      input += (char)payload[i];
    }
    perde1 = input.toInt();
  }
    if (konu == "Perde2") {
              String input = "";
    for (int i = 0; i < length; i++)
    {
      input += (char)payload[i];
    }
    perde2  = input.toInt();
  }
   if (konu == "perde3") {
    String input = "";
    for (int i = 0; i < length; i++)
    {
      input += (char)payload[i];
    }
    perde3 = input.toInt();
   }

   if (konu == "lamba1") {
    String input = "";
    for (int i = 0; i < length; i++)
    {
      input += (char)payload[i];
    }
    led1 = input.toInt();
   }

   if (konu == "lamba2") {
    String input = "";
    for (int i = 0; i < length; i++)
    {
      input += (char)payload[i];
    }
    led2 = input.toInt();
   }

   if (konu == "lamba3") {
    String input = "";
    for (int i = 0; i < length; i++)
    {
      input += (char)payload[i];
    }
    led3 = input.toInt();
   }

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // ... and resubscri
      client.subscribe("Perde1");
      client.subscribe("Perde2");
      client.subscribe("Perde3");
      client.subscribe("lamba1");
      client.subscribe("lamba2");
      client.subscribe("lamba3");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {

  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  servoMotor1.attach(D1);
  servoMotor2.attach(D2);
  servoMotor3.attach(D3);
  pinMode(ledPin1, OUTPUT); // Pinleri çıkış olarak ayarla
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
 Servo1();
 Servo2();
 Servo3();
 lamba1();
 lamba2();
 lamba3();
}

void Servo1(){
      if (perde1 == 1) {
        servoMotor1.write(90); 
        }
    if (perde1 == 0){

        servoMotor1.write(270); 
    }
    }
   
  void Servo2(){
      if (perde2 == 1) {
      servoMotor2.write(90); 
    }
   if(perde2 == 0) {
     servoMotor2.write(270); 
    }
  }

  void Servo3(){
      if (perde3 == 1) {
      servoMotor3.write(90); 
    }
   if(perde3 == 0) {
     servoMotor3.write(270); 
    }
  }


 void lamba1(){
  if (led1 == 1) {
    digitalWrite(ledPin1, HIGH); // İlk LED'i yak
    }
   if(led1 == 0) {
     digitalWrite(ledPin1, LOW); // İlk LED'i yak
    
    }
 }


 void lamba2(){
  if (led2 == 1) {
        digitalWrite(ledPin2, HIGH); // İlk LED'i yak

    }
   if(led2 == 0) {
        digitalWrite(ledPin2, LOW); // İlk LED'i yak

    }  
 }
 
 void lamba3(){
  if (led3 == 1) {
    digitalWrite(ledPin3, HIGH); // İlk LED'i yak
    }
    
   if(led3 == 0) {
    digitalWrite(ledPin3, LOW); // İlk LED'i yak
    } 
    
 }
 
