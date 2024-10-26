#include <Servo.h>
#include <LiquidCrystal.h>

Servo myservo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int irPin = 6;
const int servoPin = 9;
const unsigned long holdTime = 2000; // Hold at 90 degrees for 5 seconds

unsigned long lastDetectionTime = 0;
bool isAt90 = false;

void setup() {
    myservo.attach(servoPin);
    pinMode(irPin, INPUT);

    lcd.begin(16, 2);
    lcd.print("Ready for next"); 
}

void loop() {
    int irState = digitalRead(irPin);

    if (irState == LOW && !isAt90) { 
        myservo.write(90); 
        lcd.clear();
        lcd.print("Object detected");
        lcd.setCursor(0, 1);
        lcd.print("Servo at 90 deg");
        isAt90 = true;
        lastDetectionTime = millis();
    } 

    if (isAt90 && millis() - lastDetectionTime >= holdTime && irState == HIGH) { 
        myservo.write(0);
        lcd.clear();
        lcd.print("Object undetected");
        lcd.setCursor(0, 1);
        lcd.print("Servo at 0 deg");
        isAt90 = false;
    }
}
