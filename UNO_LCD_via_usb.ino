#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include "RTC.h"
#include "LcdLocation.h"

#define DHT_PIN 10
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27);
DHT dht(DHT_PIN, DHTTYPE);
virtuabotixRTC myRTC(2, 3, 4);

void setup(){
        Serial.begin(9600);
        lcd.begin();
        lcd.blacklight();
}

void loop(){
        float UNOtemperature = dht.readTemperature();
        float UNOhumidity = dht.readHumidity();
        if(Serial.read() == "Start_UNO") {
                Serial.println("OK");
                temperature = Serial.read();
                humidity = Serial.read();
                lightmeter = Serial.read();
                israin = Serial.read();
                airdust = Serial.read();
                adc_value = Serial.read();
                Serial.println(dht.readTemperature());
                Serial.println(dht.humidity());
                //myRTC.setDS1302Time(10, 39, 8, 5, 15, 1, 2016);
        }


        myRTC.updateTime();
        RTCtime();
}
