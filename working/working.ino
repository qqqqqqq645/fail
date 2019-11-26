#include <DHT11.h>
#include <SoftwareSerial.h>
#include <Servo.h>
int pin=6;  //Signal 이 연결된 아두이노의 핀번호
DHT11 dht11(pin);
SoftwareSerial btSerial(8,7); 
//char mode [2] = {'a','c'};    
char mode [4] = {'s','e','t','0'}; //mode '0' :automatically control, mode '1' :manually control default is 0
//String botCtrl [5] = {"fowd","back","tnle","tnri","stop"};
char botCtrl [5][4] = {{'f','o','w','d'},{'b','a','c','k'},{'t','n','l','e'},{'t','n','r','i'},{'s','t','o','p'}};
int moveStat=4;
  Servo servoLeft;
  Servo servoRight;
    char command [4];
void setup() {
   Serial.begin(9600); //통신속도 설정
   btSerial.begin(9600);

   
   Serial.print("$$$");// BT AT통신모드
   delay(1000);
   Serial.print("so,discon \r");//먼저 연결된 블루투스연결 제거
   delay(100);
   Serial.print("---"); 
   delay(100);
     servoLeft.attach(13);                      // Attach left signal to pin 13
   servoLeft.writeMicroseconds(1500);  
                                          // 1.7 ms full speed counterclockwise
   servoRight.attach(12);                     // Attach left signal to pin 12
   servoRight.writeMicroseconds(1500);  
   btSerial.listen();
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
  */
if(btSerial.available()){
  btSerial.print("temp: ");

  btSerial.print(temp);

  btSerial.print(" humi: ");

  btSerial.print(humi);

  btSerial.print("\n");

  if(mode[3] == '1'){
    Serial.print("i=");
    Serial.print(moveStat);
    motorController(moveStat);
    btSerial.print("\r");
  }
  delay(1000);
}

void motorController(int stat){
  switch(stat){
    case 0:
      servoLeft.writeMicroseconds(1600);  
      servoRight.writeMicroseconds(1400); 
      break;
    case 1:
      servoLeft.writeMicroseconds(1400);  
      servoRight.writeMicroseconds(1600); 
      break;

    case 2:
      servoLeft.writeMicroseconds(1400);  
      servoRight.writeMicroseconds(1400); 
      break;

    case 3:
      servoLeft.writeMicroseconds(1600);  
      servoRight.writeMicroseconds(1600); 
      break;
    case 4:
      servoLeft.writeMicroseconds(1500);  
      servoRight.writeMicroseconds(1500); 
      break;
   
   
  }
}

void cmdController(){
   if(btSerial.available()>0){
    for(int i=0;i<4;i++){
       command[i] = btSerial.read();
    } 

    if((command[0]==mode[0]) && (command[1]==mode[1]) &&
         (command[2]==mode[2])){
          if(command[3] != mode[3]){
            if(command[3] == '0'){
              mode[3]='0';
              btSerial.print("Changed to automode\n");
            }
            else if(command[3] == '1'){
              mode[3] = '1';
              btSerial.print("Changed to manual mode\n");
            }
          }
         }
      else {
        for(int i=0;i<5;i++){
          if((command[0]==botCtrl[i][0])&& (command[1]==botCtrl[i][1])&&
            (command[2]==botCtrl[i][2])&&(command[3]==botCtrl[i][3])){
               btSerial.print("movecmd acyibated\n");
               moveStat = i;
            }
        }
     }
  }

}
