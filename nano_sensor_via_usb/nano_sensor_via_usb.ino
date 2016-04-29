

#include <DHT.h>
#include <BH1750.h>

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

void setup(){
        Serial.begin(9600);
}

void loop(){
        if(dht.readTemperature() >= 0
           && dht.readTemperature() <= 40
           && dht.readHumidity() >= 0
           && dht.readHumidity() <= 100) {
                if (Serial.read() == "Start_nano") {
                        Serial.println("OK");
                        Serial.println(dht.readTemperature());
                        Serial.println(dht.readHumidity());
                        Serial.println(lightmeter.readLightLevel());
                        Serial.println(digialRead(RAINda));
                        Serial.println(airdust());
                        Serial.println(adcAverage());
                }
        }
        delay(1000);
}

float airdust(){
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
