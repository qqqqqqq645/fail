#include <DHT11.h>

int pin=6;  //Signal 이 연결된 아두이노의 핀번호
DHT11 dht11(pin);

void setup() {
   Serial.begin(9600); //통신속도 설정  
  Serial.print("$$$"); // Bt AT Command mod begin
  delay(3000);

  Serial.print("u,115k \r"); // Android phone reliable pairing time

  Serial.print("---"); // Return to the Data mode
  delay(100);
  Serial.begin(115200);



}

void loop() {
  delay(1500);
   float temp, humi;
  dht11.read(humi, temp);
  Serial.print("temp:");
  Serial.print(temp);
  Serial.print(" humi:");
  Serial.print(humi);
  Serial.print("\n");
  delay(1500);

 
  }


  
