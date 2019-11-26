#include <DHT11.h>
#include <SoftwareSerial.h>

int pin=6;  //Signal 이 연결된 아두이노의 핀번호
DHT11 dht11(pin);
SoftwareSerial btSerial(8,7); 

void setup() {
   Serial.begin(115200); //통신속도 설정
    btSerial.begin(115200);
  

   delay(100);

   btSerial.print("welcome");
 
}

void loop() {
     while(btSerial.listen()==0)
         Serial.print("x\n");
  float temp, humi;
  dht11.read(humi, temp);
  //Serial.print(btSerial.listen());
  Serial.print("온도:");
  Serial.print(temp);
  Serial.print(" 습도:");
  Serial.print(humi);
  Serial.print("\n");
  delay(1500);

 
 if(btSerial.available()<=0){
  
      btSerial.print("temp: ");
      btSerial.print(temp);
      btSerial.print(" humi: ");
      btSerial.print(humi);
      btSerial.print("\n");
    }
    else{
        char chk;
        while(btSerial.available()){
        chk=btSerial.read();
        btSerial.print(chk);
       }
    }
  }


  
