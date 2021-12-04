#define s0 4        //Module pins wiring
#define s1 5
#define s2 6
#define s3 7
#define out 8

#define SENSOR 9
#define pwm1 44
#define pwm2 46
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int relay1 = 2; //pin2
const int relay2 = 3; //pin3

int Red = 0, Blue = 0, Green = 0; //RGB values

unsigned long interval = 2000; // the time we need to wait
unsigned long previousMillis = 0; // millis() returns an unsigned long.

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

  pinMode(s0, OUTPUT);   //pin modes
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  digitalWrite(s0, HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
  digitalWrite(s1, HIGH); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%

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

    if (Red < Blue && Red <= Green && Red < 23) {
      Serial.println(" - RED detected!");
      digitalWrite(relay1, relayON);
    }

    else if (Red <= 15 && Green <= 15 && Blue <= 15)  {
      Serial.println(" - WHITE detected!");
      digitalWrite(relay1, relayOFF);
      delay(3000);
      analogWrite(pwm1, 0);
      analogWrite(pwm2, 30);
    }

    else if (Blue < Green && Blue < Red && Blue < 20)
      Serial.println("Blue");

    else if (Green < Red && Green - Blue <= 8)
      Serial.println("Green");

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
  digitalWrite(s2, LOW);                                           //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
  digitalWrite(s3, LOW);
  Red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again, if you have trouble with this expression check the bottom of the code
  delay(100);
  digitalWrite(s3, HIGH);                                         //Here we select the other color (set of photodiodes) and measure the other colors value using the same techinque
  Blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(100);
  digitalWrite(s2, HIGH);
  Green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(100);
}
