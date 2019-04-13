int MoPin = 9;    // vibrator Grove connected to digital pin 9

void setup()  {
    pinMode( MoPin, OUTPUT );
    Serial.begin(9600);
}

void loop()  {

    digitalWrite(MoPin, HIGH);
    delay (1000); 
    digitalWrite(MoPin, LOW);
    int delaytime = random (3,6)*1000;
    delay (delaytime);
    Serial.println(delaytime);
}
