#include <DHT11.h>
#include <SoftwareSerial.h>

int pin=6;  //Signal 이 연결된 아두이노의 핀번호
DHT11 dht11(pin);
//SoftwareSerial btSerial(8,7); 
    
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
  /*  
  Serial.print("온도:");
  Serial.print(temp);
  Serial.print(" 습도:");
  Serial.print(humi);
  Serial.println();
  delay(1500); //1초마다 측정
*/
    while(Serial.available()>0){
      char chk;
        chk=Serial.read();
        if(chk == 'e'){
          Serial.print("temp: ");
          Serial.print(temp);
          Serial.print(" humi: ");
          Serial.print(humi);
          Serial.print("\r");
    }
    else{
      Serial.print(chk);
    }
  }
  
/*  while(btSerial.available()>0){
    char chk;
    chk=btSerial.read();
    if(chk == 'e'){
      btSerial.print("temp: ");
      btSerial.print(temp);
      btSerial.print(" humi: ");
      btSerial.print(humi);
      btSerial.print("\r");
    }
    else{
      btSerial.print(chk);
    }
  }
  */
  
}
