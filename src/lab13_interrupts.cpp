/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/Labs/lab13_interrupts/src/lab13_interrupts.ino"
#include "oled-wing-adafruit.h"
void isr();
void setup();
void loop();
#line 2 "d:/Labs/lab13_interrupts/src/lab13_interrupts.ino"
OledWingAdafruit display;
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);
volatile bool interruptOccured = false;

volatile int count = 0;

void isr()
{
  count++;
  interruptOccured = true;
}

bool press = false;

void setup()
{
  pinMode(D6, INPUT_PULLUP); //counter increaser
  pinMode(D5, INPUT);        //interrupter
  pinMode(D7, OUTPUT);
  attachInterrupt(D6, isr, FALLING);
  Serial.begin(9600);
  display.setup();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Test");
  display.display();
}

void loop()
{
  display.loop();
  
  if (interruptOccured)
  {
    interruptOccured = false;
    Serial.println(count);
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(count);
    display.display();
    delay(500);
  }
  if (digitalRead(D5) == LOW)
    {
      if (press == false) 
      {
        noInterrupts();
        press = true;
      } 
        else 
      {
        interrupts();
        press = false;
      }
      Serial.println("pressed");
      //digitalWrite(D7, HIGH);
      delay(500);
  }
  delay(1000);  
}
