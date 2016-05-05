

#include <DHT.h>
#include <BH1750.h>

#define DHT_PIN 10
#define DHTTYPE DHT11
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
String getWord = "";

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0)
  {
    digitalWrite(13, HIGH);
    char Serial_Buffer = Serial.read();
    if (Serial_Buffer != '\n') {
      getWord += Serial_Buffer;
      // Serial.println(getWord);
    }
    else
    {
      if (getWord == "Start_nano\r") {
        digitalWrite(13, LOW);
        Serial.println("OK");
        Serial.println(dht.readTemperature());
        Serial.println(dht.readHumidity());
        Serial.println(lightMeter.readLightLevel());
        Serial.println(digitalRead(RAINda));
        Serial.println(airdust());
        Serial.println(adcAverage());
      }
      getWord = "";
    }
  }

}

float airdust() {
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

