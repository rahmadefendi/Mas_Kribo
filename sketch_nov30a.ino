// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

#define SENSOR 9
#define pwm1 44
#define pwm2 46
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int relay1 = 2; //pin2
const int relay2 = 3; //pin3

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

unsigned long interval = 2000; // the time we need to wait
unsigned long previousMillis = 0; // millis() returns an unsigned long.

int relayON = LOW; //relay nyala
int relayOFF = HIGH; //relay mati

unsigned long lastMillis1;

void setup() {

  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  digitalWrite(relay1, relayOFF);
  digitalWrite(relay2, relayOFF);

  pinMode(SENSOR, INPUT_PULLUP);
  Serial.println(" Deteksi Sensor IR " );
  delay(1000);

  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);

  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);

  // Setting frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  lastMillis1 = millis();
}

void loop() {

  warna();

  int L = digitalRead(SENSOR);

  if (L == 0) {
    Serial.println("  Tedeteksi");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Terdeteksi");
    analogWrite(pwm1, 0);
    analogWrite(pwm2, 0);

    if (redColor > greenColor && redColor > blueColor) {
      Serial.println(" - RED detected!");
      digitalWrite(relay1, relayON);
    }

    else if (blueColor > redColor && blueColor > greenColor) {
      Serial.println(" - BLUE detected!");
      digitalWrite(relay1, relayOFF);
      delay(3000);
      analogWrite(pwm1, 0);
      analogWrite(pwm2, 30);
    }
  }

  else  {
    Serial.println("  Tidak terdeteksi");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tidak Terdeteksi");
    analogWrite(pwm1, 0);
    analogWrite(pwm2, 30);
    delay(1000);
  }

}


void warna() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the RED (R) frequency from 0 to 255
  // You must replace with your own values. Here's an example:
  // redColor = map(redFrequency, 70, 120, 255,0);
  redColor = map(redFrequency, 39, 103, 255, 0);

  // Printing the RED (R) value
  Serial.println("R= ");
  Serial.print(redColor);
  delay(100);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the GREEN (G) frequency from 0 to 255
  // You must replace with your own values. Here's an example:
  // greenColor = map(greenFrequency, 100, 199, 255, 0);
  greenColor = map(greenFrequency, 61, 109, 255, 0);

  // Printing the GREEN (G) value
  Serial.println(" G= ");
  Serial.print(greenColor);
  delay(100);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  // Remaping the value of the BLUE (B) frequency from 0 to 255
  // You must replace with your own values. Here's an example:
  // blueColor = map(blueFrequency, 38, 84, 255, 0);
  blueColor = map(blueFrequency, 38, 125, 255, 0);

  // Printing the BLUE (B) value
  Serial.print(" B= ");
  Serial.print(blueColor);
  delay(100);
}
