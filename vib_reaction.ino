#include <SD.h>
#include <SPI.h>


#define SD_ChipSelectPin 10
#define buttonPin 6

const int vibPin = 5;    // vibrator Grove connected to digital pin 9
//const int buttonPin = 6;

bool hasPressed = false;
unsigned int vibStamp = 0;
unsigned int pressStamp = 0;
unsigned int index = 0;
unsigned int secondsIndex = 0;
unsigned int oldTime, newTime;
int vibDelay;

void button();

void setup()  {
  pinMode(vibPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  SD.begin(SD_ChipSelectPin);
  //Skapa textfil på SD-kort om den inte finns
  if (!SD.exists("timevib.txt")) {
   File timefile = SD.open ("timevib.txt", FILE_WRITE);
   timefile.close();
  }
  oldTime = millis();
  newTime = oldTime;
}

int newVibDelay() { 
  return random(3,6);
}

void intToString(unsigned int num, char *str) {
  for(int i = 3; i >= 0; i--) {
    str[i] = (num%10) + '0';
    num /= 10;
  }
}

void loop()  {
  if(newTime - oldTime >= 1000) {
    secondsIndex++;
    if(secondsIndex == 1) {
      hasPressed = false;
      vibDelay = newVibDelay();
      vibStamp = millis();
      digitalWrite(vibPin, HIGH);
    }

    if(secondsIndex == 2) {
      digitalWrite(vibPin, LOW);
    }

    if(secondsIndex == vibDelay + 1) {
      File timefile = SD.open("timevib.txt", FILE_WRITE);
      
      timefile.print(index);
      timefile.print(" : ");
      if(hasPressed) {
        timefile.print(pressStamp - vibStamp);
        timefile.println("ms");
      }
      else {
        timefile.println("N/A");
      }
      timefile.close();
      index++;
      secondsIndex = 0;
    }
    
    oldTime = newTime;
  }
  newTime = millis();

  if(!digitalRead(buttonPin) && !hasPressed) {
    Serial.println("Has pressed");
    hasPressed = true;
    pressStamp = millis();
  }
}
