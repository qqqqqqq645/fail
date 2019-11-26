#include <DHT11.h>
#include <HuemonelabKit.h>

int pin=7;  //Signal 이 연결된 아두이노의 핀번호
DHT11 dht11(pin);
Bluetooth bluetooth(8,9); 
    
void setup() {
   Serial.begin(115200); //통신속도 설정
   bluetooth.begin(115200);
   Serial.print("$$$"); // Bt AT Command mod begin
  delay(3000);
  Serial.print("SI,0800 \r"); // Android phone reliable pairing time
  delay(100);
  Serial.print("SJ,0800 \r"); // Android phone reliable?pairing time
  delay(100);
  Serial.print("---"); // Return to the Data mode
  delay(100);
}

void loop() {
  float temp, humi;
  dht11.read(humi, temp);
    
  Serial.print("온도:");
  Serial.print(temp);
  Serial.print(" 습도:");
  Serial.print(humi);
  Serial.println();
  delay(1500); //1초마다 측정

  bluetooth.print("온도: ");
  bluetooth.print(temp);
  bluetooth.print(" 습도: ");
  bluetooth.print(humi);
}
