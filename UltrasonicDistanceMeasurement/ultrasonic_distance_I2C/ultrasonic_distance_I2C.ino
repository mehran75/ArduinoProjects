//sketch created by Akshay Joseph
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);


const int trigPin = 7, echoPin = 8, buzz = 6, red = 5, yellow = 4, blue = 3;
long duration;
int distance;

bool fault = false;

void setup()
{
  // buzzer
  pinMode(buzz, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(blue, OUTPUT);

  // ultrasonic setup
  pinMode(trigPin, OUTPUT); // trigger pin
  pinMode(echoPin, INPUT); // echo pin
  Serial.begin(9600);


  lcd.init();

  lcd.backlight();
  lcd.clear();
  lcd.noBlink();

  digitalWrite(buzz, LOW);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);


}

void loop()
{

  lcd.setCursor(0, 0);
  digitalWrite(trigPin, LOW);
  delay(10);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm\n");


  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
  if (distance < 10) {
    lcd.print("0");
  }
  if (distance > 450) {
    lcd.print("> ");
    distance = 450;
  }
  lcd.print(distance);
  lcd.print(" cm    ");


  if (distance < 10) {
    digitalWrite(buzz, HIGH);
    digitalWrite(red, HIGH);
    delay(10);
    digitalWrite(buzz, LOW);
  } else if (distance < 20) {
    digitalWrite(buzz, HIGH);
    digitalWrite(yellow, HIGH);
    delay(50);
    digitalWrite(yellow, LOW);
    digitalWrite(buzz, LOW);
    digitalWrite(red, LOW);
  } else if (distance < 40) {
    digitalWrite(blue, HIGH);
    delay(200);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);

  } else {
    digitalWrite(buzz, LOW);
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(blue, LOW);
  }
  delay(100);

}
