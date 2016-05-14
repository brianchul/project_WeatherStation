#include <DHT.h>
#include <BH1750.h>
#include <Wire.h>

#define DHT_PIN 10
#define DHTTYPE DHT22
#define RAINan 7
#define RAINda 5
#define PMan 0
#define PMLGT 12
#define UV 5

BH1750 lightMeter;
DHT dht(DHT_PIN, DHTTYPE);
int measurePin = 0;                                 //Connect dust sensor to Arduino A0 pin
int ledPower = PMLGT;                               //Connect 3 led driver pins of dust sensor to Arduino D30
float calcVoltage = 0;
float dustDensity = 0;
float UVlight = 0;
unsigned int adc_value = 0;
String getWord;
int airdusts;
float adcs;
long timer;


void setup() {
  Serial.begin(9600);
  timer = millis();
  lightMeter.begin();
  pinMode(RAINda, INPUT);
}

void loop() {
  if (millis() - timer >= 5000) {
    adcs = adcAverage();
    airdusts = airdust();
    timer = millis();
  }
  if (Serial.available() > 0)
  {
    char Serial_Buffer = Serial.read();
    if (Serial_Buffer != '\r' && Serial_Buffer != '\n') {
      switch (Serial_Buffer) {
        case 'T':
          Serial.println(dht.readTemperature());
          break;
        case 'H':
          Serial.println(dht.readHumidity());
          break;
        case 'L':
          Serial.println(lightMeter.readLightLevel());
          break;
        case 'R':
          Serial.println(rainDa());
          break;
        case 'A':
          Serial.println(airdusts);
          break;
        case 'U':
          Serial.println(adcs);
          break;
      }
    }
  }

}

int airdust() {
  digitalWrite(PMLGT, LOW);
  delayMicroseconds(280);
  float voMeasure = analogRead(PMan);
  delayMicroseconds(40);
  digitalWrite(PMLGT, HIGH);
  return voMeasure;
}

unsigned int adcAverage()
{
  unsigned char samples = 64;
  unsigned long avg = 0;
  while (samples > 0)
  {
    avg = (avg + analogRead(UV));
    delayMicroseconds(4);
    samples--;
  }
  avg >>= 6;
  return avg;
}
bool rainDa() {
  if (digitalRead(RAINda) == 0)
    return 1;
  else return 0;

}

