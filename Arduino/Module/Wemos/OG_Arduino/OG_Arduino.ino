#include <ESP8266WiFi.h>

#include <FirebaseArduino.h>

 

#define FIREBASE_HOST "****.firebaseio.com" // http달린거 빼고 적어야 됩니다.

#define FIREBASE_AUTH "" // 데이터베이스 비밀번호

#define WIFI_SSID "" // 연결 가능한 wifi의 ssid

#define WIFI_PASSWORD "" // wifi 비밀번호

 

 

void setup() {

  // put your setup code here, to run once:

  pinMode(LED_BUILTIN,OUTPUT);

  digitalWrite(LED_BUILTIN,0);

  

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("connecting");

  

  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");

    delay(500);

   }

  Serial.println();

  Serial.print("connected: ");

  Serial.println(WiFi.localIP());

  

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Firebase.setInt("LEDStatus",0);

}

 

void loop() {

  //light on

  if(Firebase.getInt("LEDStatus")==1) {

    digitalWrite(LED_BUILTIN,HIGH);

    Serial.print("LED is high");

    Serial.println();

  }

  //light off

  else if (Firebase.getInt("LEDStatus")==0){

    digitalWrite(LED_BUILTIN,LOW);

    Serial.print("LED is low");

    Serial.println();

  }

  

  if (Firebase.failed()) {// Check for errors

    Serial.print("setting /number failed:");

    Serial.println(Firebase.error());

    return;

  }

  delay(1000);

}
