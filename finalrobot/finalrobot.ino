#include <Servo.h>          // Include servo library
#include <DHT11.h>          // Include Dht11 sensor
Servo servoLeft;          // Declare left and right servos
Servo servoRight;
DHT11 dht11(6);  //Setting DHT11 Pin number
void setup() // Built-in initialization block
{
  pinMode(4, INPUT); pinMode(5, OUTPUT);// Left floor IR LED & Receiver
  pinMode(7, INPUT); pinMode(8, OUTPUT);// Right floor IR LED & Receiver
  pinMode(9, INPUT); pinMode(10, OUTPUT);//Left IR LED & Receiver
  pinMode(2, INPUT); pinMode(3, OUTPUT);//Right IR LED & Receiver
  servoLeft.attach(13);      
  servoRight.attach(12); 
  Serial.begin(9600); // Set data rate to 9600 bps
} 
void loop() 
{
  
  int irFloorLeft = irDetect(5, 4, 43000); // Check for floor
  int irFloorRight = irDetect(8,7,43000); //right floor check
  int irLeft = irDetect(10, 9, 38000);  // Check for object on left
  int irRight = irDetect(3, 2, 38000);
  //send Data to Serial(bluetooth)
  float temp, humi;
  dht11.read(humi, temp);
  Serial.print("temp:");
  Serial.print(temp);
  Serial.print(" humi:");
  Serial.print(humi);
  Serial.print("\n");
   // Display 1/0 no detect/detect
  delay(100); } // 0.1 second delay


// IR Object Detection Function
int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8); // IRLED 38 kHz for at least 1 ms
  delay(1); // Wait 1 ms
  int ir = digitalRead(irReceiverPin); // IR receiver -> ir variable
  delay(1); // Down time before recheck
  return ir; // Return 1 no detect, 0 detect
} 
