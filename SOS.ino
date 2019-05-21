#include <TinyGPS.h>
#include <SoftwareSerial.h>
SoftwareSerial Gsm(8, 7);

const int buttonPin = 2;
int buttonState = 0; 
const int ledPin =  13;  
const int sOFF =  12;
//unsigned long lastGPS = 0;

char phone_no[] = "9902061316";
 
TinyGPS gps;
 
void setup()
{
  Serial.begin(9600);
  Gsm.begin(9600);  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(sOFF, OUTPUT);
  digitalWrite(sOFF, LOW);
}
 
void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  buttonState = digitalRead(buttonPin);
  int count =0;
  
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      Serial.print(c);
      if (gps.encode(c)) 
        newData = true;  
    }
  }
 
  if (buttonState == HIGH && newData == true)      //If newData is true
  {
    //lastGPS = millis();
    count =1;
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);   
    Gsm.print("AT+CMGF=1\r"); 
    delay(400);
    Gsm.print("AT+CMGS=\"");
    Gsm.print(phone_no);
    Gsm.println("\"");
    
    delay(300);
    Gsm.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    //Gsm.print(" Longitude = ");
    Serial.print(",");
    Gsm.print(",");
    Gsm.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    delay(200);
    Gsm.println((char)26);
    delay(200);
    digitalWrite(ledPin, HIGH);
    Gsm.println();
    delay(20000);
 
  }

  digitalWrite(ledPin, LOW);
  Serial.println(failed);
//  if (chars == 0)
//  Serial.println("** No characters received from GPS: check wiring **");
}
