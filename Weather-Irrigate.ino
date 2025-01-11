#include <Servo.h>
#include <LiquidCrystal.h>

#define SOIL_MOISTURE_PIN A0
#define RELAY_PIN 8
#define LDR_LEFT A1
#define LDR_RIGHT A2
#define SERVO_PIN 9

Servo servoMotor;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int soilMoistureThreshold = 600;
int ldrLeftValue = 0;
int ldrRightValue = 0;
int soilMoistureValue = 0;
int servoPosition = 90;

void setup() {
  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LDR_LEFT, INPUT);
  pinMode(LDR_RIGHT, INPUT);

  servoMotor.attach(SERVO_PIN);
  servoMotor.write(servoPosition);

  lcd.begin(16, 2);
  lcd.print("Irrigation & Light");
  delay(2000);
  lcd.clear();
}

void loop() {
  soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
  lcd.setCursor(0, 0);
  lcd.print("Soil: ");
  lcd.print(soilMoistureValue);

  if (soilMoistureValue < soilMoistureThreshold) {
    digitalWrite(RELAY_PIN, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Irrigating...    ");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Soil OK         ");
  }

  ldrLeftValue = analogRead(LDR_LEFT);
  ldrRightValue = analogRead(LDR_RIGHT);

  if (ldrLeftValue > ldrRightValue + 50) {
    servoPosition = constrain(servoPosition - 5, 0, 180);
  } else if (ldrRightValue > ldrLeftValue + 50) {
    servoPosition = constrain(servoPosition + 5, 0, 180);
  }
  servoMotor.write(servoPosition);

  lcd.setCursor(0, 1);
  lcd.print("L:");
  lcd.print(ldrLeftValue);
  lcd.print(" R:");
  lcd.print(ldrRightValue);

  delay(500);
}
