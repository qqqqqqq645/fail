void setup() // Built-in initialization block
{
 // Play tone for 1 second
delay(1000); // Delay to finish tone
pinMode(2, INPUT); pinMode(3, OUTPUT);// Left IR LED & Receiver
pinMode(9, INPUT); pinMode(10, OUTPUT);// Right IR LED & Receiver
Serial.begin(9600); // Set data rate to 9600 bps
} 
void loop() // Main loop auto-repeats
{
int irLeft = irDetect(3, 2, 43000); // Check for object
int irRight = irDetect(10,9,43000); //right check
Serial.print("right=");
Serial.print(irRight);
Serial.print("left=");
Serial.println(irLeft); // Display 1/0 no detect/detect
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
