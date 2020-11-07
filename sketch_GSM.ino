
#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8); // gsm module connected here
String textForSMS;

int FlameSensor = 4; // Flame Sensor
int Buzzer = 5; // Alarm/light can be connected with this Buzzer
const int rs = 11 , en = 9 , d4 = 8 , d5 = 6, d6 = 4, d7 = 3;
void setup() {

randomSeed(analogRead(0));
Serial.begin(9600);
SIM900.begin(9600); // original 19200. while enter 9600 for sim900A
Serial.println(" logging time completed!");
pinMode(FlameSensor, INPUT);  
delay(1000); // wait for 5 seconds
  
}

void loop() {

  
  if ( digitalRead(FlameSensor) == HIGH) // 
  {
  textForSMS =  "\nFire Detected!";  
  tone(Buzzer, 1000, 1000);
  sendSMS(textForSMS);
  Serial.println(textForSMS);
  Serial.println("message sent."); 
  delay(1000);
  }
  if ( digitalRead(FlameSensor) == LOW) // 
  {
  Serial.println("No Fire Detected"); 
  delay(1000);
  }
  
}


void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(1000);
 SIM900.println("AT + CMGS = \"+923339537499\"");  // recipient's mobile number, in international format
 
  delay(1000);
  SIM900.println(message);                         // message to send
  delay(1000);
  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(1000); 
  SIM900.println();
  delay(100);                                     // give module time to send SMS
 
}
