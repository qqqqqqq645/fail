#include <DHT11.h>
#include <SoftwareSerial.h>

int pin=6;  //Signal 이 연결된 아두이노의 핀번호
DHT11 dht11(pin);
SoftwareSerial btSerial(8,7); 

void setup() {
   Serial.begin(9600); //통신속도 설정
    btSerial.begin(9600);
   Serial.print("$$$");// BT AT통신모드
   delay(1000);
   Serial.print("so,discon \r");//먼저 연결된 블루투스연결 제거
   delay(100);
   Serial.print("---"); 
   delay(100);
 
}

void loop() {
  float temp, humi;
  dht11.read(humi, temp);
  
  Serial.print("온도:");
  Serial.print(temp);
  Serial.print(" 습도:");
  Serial.print(humi);
  delay(1500);

 
 if(btSerial.available()<=0){
    
      btSerial.print("temp: ");
      btSerial.print(temp);
      btSerial.print(" humi: ");
      btSerial.print(humi);
    }
    else{
      char chk;
      while(btSerial.available()){
        chk=btSerial.read();
        btSerial.print(chk);
      }
    }

    while(btSerial.available())
     btSerial.read();
  }

  
