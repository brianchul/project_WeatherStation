#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>


#define DHT_PIN 10
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27);
DHT dht(DHT_PIN, DHTTYPE);
virtuabotixRTC myRTC(2, 3, 4);
String getWord = " ";
float temperature, humidity;
int lightmeter, israin, airdust, adc_value;

void setup() {
  Serial.begin(9600);
  lcd.begin(20,4);
//  lcd.blacklight();
  lcd.home();
  lcdloc();
}

void loop() {
  float UNOtemperature = dht.readTemperature();
  float UNOhumidity = dht.readHumidity();
  if (Serial.available() > 0)
  {
    char Serial_Buffer = Serial.read();
    if (Serial_Buffer != '\n')                          // still input the String data
    {
      getWord += Serial_Buffer;
      Serial.println(Serial_Buffer);
    }
    else                                                          // finished trasmitting the data
    {
      if (getWord == "Start_UNO") {
        Serial.println("OK");
        temperature = Serial.read();
        humidity = Serial.read();
        lightmeter = Serial.read();
        israin = Serial.read();
        airdust = Serial.read();
        adc_value = Serial.read();
        Serial.println(dht.readTemperature());
        Serial.println(dht.readHumidity());
        //myRTC.setDS1302Time(10, 39, 8, 5, 15, 1, 2016);
        getWord = "";
        showDataLCD();
      }
      else if(getWord == "Adj_time"){
        Serial.println("OK");
        int seconds = Serial.read();
        int minutes = Serial.read();
        int hours = Serial.read();
        int dayofweek = Serial.read();
        int dayofmonth = Serial.read();
        int months = Serial.read();
        int years = Serial.read();
        myRTC.setDS1302Time(seconds, minutes, hours, dayofweek, dayofmonth, months, years);
    }
  }


  myRTC.updateTime();
  RTCtime();
}

void lcdloc() {

        lcd.setCursor(0, 0);
        lcd.print("TMP:");

        lcd.setCursor(9, 0);
        lcd.print("C ");

        lcd.setCursor(0, 1);
        lcd.print("HUM: ");

        lcd.setCursor(9, 1);
        lcd.print("% ");

        lcd.setCursor(11, 2);
        lcd.print("DST:");

        // lcd.setCursor(9, 2);
        // lcd.print(" ug/m3");

        lcd.setCursor(11, 0);
        lcd.print("RAIN: ");

        lcd.setCursor(11, 1);
        lcd.print("LGT:");
}


void showDataLCD(){
        //temperature
        lcd.setCursor(5,0);
        lcd.print(temperature);
        //humidity
        lcd.setCursor(5,1);
        lcd.print(humidity);
        //還沒調整 rain
        lcd.setCursor(17,0);
        lcd.print(israin);
        //airdust
        if(airdust < 1000) {
                lcd.setCursor(16, 2);
                lcd.print("0");
                lcd.setCursor(17, 2);
                lcd.print(airdust);
        } else {
                lcd.setCursor(16, 2);
                lcd.print(airdust);
        }
        //lightmeter
        if (lightmeter < 10) {
                lcd.setCursor(16, 1);
                lcd.print("000");
                lcd.setCursor(19, 1);
                lcd.print(lightmeter);
        } else if (lightmeter < 100 && lightmeter >= 10) {
                lcd.setCursor(16, 1);
                lcd.print("00");
                lcd.setCursor(18, 1);
                lcd.print(lightmeter);
        } else if (lightmeter < 1000 && lightmeter >= 100) {
                lcd.setCursor(16, 1);
                lcd.print("0");
                lcd.setCursor(17, 1);
                lcd.print(lightmeter);
        }  else {
                lcd.setCursor(16, 1);
                lcd.print(lightmeter);
        }
}

void RTCtime() {
        lcd.setCursor(0, 2);
        lcd.print(myRTC.year);
        lcd.setCursor(4, 2);
        lcd.print("/");

        if (myRTC.month < 10) {
                lcd.setCursor(5, 2);
                lcd.print("0");
                lcd.setCursor(6, 2);
                lcd.print(myRTC.month);
        } else {
                lcd.setCursor(5, 2);
                lcd.print(myRTC.month);
        }

        lcd.setCursor(7, 2);
        lcd.print("/");

        if (myRTC.dayofmonth < 10) {
                lcd.setCursor(8, 2);
                lcd.print("0");
                lcd.setCursor(9, 2);
                lcd.print(myRTC.dayofmonth);
        } else {
                lcd.setCursor(8, 2);
                lcd.print(myRTC.dayofmonth);
        }

        if (myRTC.hours < 10) {
                lcd.setCursor(11, 3);
                lcd.print("0");
                lcd.setCursor(12, 3);
                lcd.print(myRTC.hours);
        } else {
                lcd.setCursor(11, 3);
                lcd.print(myRTC.hours);
        }

        lcd.setCursor(13, 3);
        lcd.print(":");

        if (myRTC.minutes < 10) {
                lcd.setCursor(14, 3);
                lcd.print("0");
                lcd.setCursor(15, 3);
                lcd.print(myRTC.minutes);
        } else {
                lcd.setCursor(14, 3);
                lcd.print(myRTC.minutes);
        }

        lcd.setCursor(16, 3);
        lcd.print(":");

        if (myRTC.seconds < 10) {
                lcd.setCursor(17, 3);
                lcd.print("0");
                lcd.setCursor(18, 3);
                lcd.print(myRTC.seconds);
        } else {
                lcd.setCursor(17, 3);
                lcd.print(myRTC.seconds);
        }
        lcd.setCursor(0, 3);
        weeks();
}

char weeks() {
        switch (myRTC.dayofweek) {
        case 0:
                lcd.print(" Sunday!");
                break;
        case 1:
                lcd.print(" Monday!");
                break;
        case 2:
                lcd.print(" Tuesday!");
                break;
        case 3:
                lcd.print(" Wednesday");
                break;
        case 4:
                lcd.print(" Thursday!");
                break;
        case 5:
                lcd.print(" Friday!");
                break;
        case 6:
                lcd.print(" Saturday!");
                break;
        }
}
