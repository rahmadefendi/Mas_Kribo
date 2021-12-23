#include <Wire.h> // i2C Conection Library
#include <LiquidCrystal_I2C.h> //i2C LCD Library 

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SENSOR 9
#define pwm1 44
#define pwm2 46

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8 
int frequencyr = 0; 
int frequencyg = 0; 
int frequencyb = 0;
int jumlah;

const int relay1 = 2; //pin2
const int relay2 = 3; //pin3
int relayON = LOW; //relay nyala
int relayOFF = HIGH; //relay mati

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
  
  pinMode(S0, OUTPUT); 
  pinMode(S1, OUTPUT); 
  pinMode(S2, OUTPUT); 
  pinMode(S3, OUTPUT); 
  pinMode(sensorOut, INPUT); 
  digitalWrite(S0,HIGH); 
  digitalWrite(S1,LOW); 
 
}

void loop() {
  int L = digitalRead(SENSOR);

  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
frequencyr = pulseIn(sensorOut, LOW);
delay(100); 
digitalWrite(S2,HIGH); 
digitalWrite(S3,HIGH);
frequencyg = pulseIn(sensorOut, LOW);
delay(100); 
digitalWrite(S2,LOW); 
digitalWrite(S3,HIGH);
frequencyb = pulseIn(sensorOut, LOW); 

  if (L == 0) {
    Serial.println("  Tedeteksi");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Terdeteksi");
    analogWrite(pwm1, 0);
    analogWrite(pwm2, 0);
    
if((frequencyr > 30)&&(frequencyr < 38)&&(frequencyg > 49)&&(frequencyg < 61)&&(frequencyb > 42)&&(frequencyb < 51))
{
lcd.setCursor(0, 1);
lcd.println("NODA");
 digitalWrite(relay1, relayON);
      delay(1000);
       digitalWrite(relay1, relayOFF);
      delay(1000);
}
else if((frequencyr > 22)&&(frequencyr < 24)&&(frequencyg > 36)&&(frequencyg
< 49)&&(frequencyb > 36)&&(frequencyb < 45))
{
lcd.setCursor(0, 1);
lcd.println("NODA");
 digitalWrite(relay1, relayON);
      delay(1000);
       digitalWrite(relay1, relayOFF);
      delay(1000);
}

  }
   else  {
    Serial.println("  Tidak terdeteksi");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tidak Terdeteksi");
    analogWrite(pwm1, 12);
    analogWrite(pwm2, 0);
    delay(1000);
  }

}
