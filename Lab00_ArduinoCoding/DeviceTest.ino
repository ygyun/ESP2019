#include <LiquidCrystal.h>
#include <Servo.h>
#include "LCD.h"

int melody[] = {262,294,330,349,392,440,494,523};
int len[] =    {100,100,100,100,100,100,100,100};
LiquidCrystal lcd(12,11,2,3,4,5);
Servo myservo;
LCD test;

void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
  
  lcd.begin(16,2);
  myservo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  int light = analogRead(A0);
  int ledLightR = map(light, 0, 1023, 255, 0);
  int ledLightG = map(light, 0, 1023, 255, 0);
  int ledLightB = map(light, 0, 1023, 255, 0);

  for(int i=0; i<8; i++)
  {
    tone(8, melody[i], len[i]);
    delay(400);
    noTone(8);
  }


  analogWrite(13,0);
  analogWrite(10,0);
  analogWrite(1,0);

  digitalWrite(7, HIGH);
  delayMicroseconds(10);
  digitalWrite(7, LOW);

  long duration = pulseIn(6, HIGH);
  if( duration == 0 )
  {
    return;
  }

  long distance = duration / 58.2;
  if( distance < 10 )
  {
    analogWrite(13, 255);
  }
  else if( distance < 20 )
  {
    analogWrite(10, 255);
  }
  else if( distance < 30 )
  {
    analogWrite(1, 255);
  }
  delay(100);

  lcd.clear();
  lcd.print("Light: ");
  lcd.print(light);
  lcd.setCursor(0,1);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm");
  delay(500);

  for( int i=0; i<90; ++i)
  {
    myservo.write(i);
    delay(1);
  }
    delay(100);

  myservo.write(0);
  delay(1000);
}
