#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>
#include <Wire.h>


#define DHT_PIN 10
#define DHTTYPE DHT22

LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(DHT_PIN, DHTTYPE);
virtuabotixRTC myRTC(2, 3, 4);
float temperature, humidity, UNOtemperature, UNOhumidity;
int lightmeter, israin, airdust, adc_value;
char keyword;
String showNumber = "";

void lcdloc();
void showDataLCD();
char weeks();
void RTCtime();

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcdloc();

  pinMode(8, INPUT);
}
/*
temp = 10000 + xx.xx
hum = 20000 + xx.xx
light = 30000
israin = 40000
aitdust = 50000
adc = 60000
*/
void loop() {
  if (digitalRead(8) == HIGH)lcd.backlight();
  else lcd.setBacklight(0);

  keyword = getData()[0];
  switch (keyword) {
    case 'T':
      temperature = stringToLong(getData()) / 10.0;
      break;
    case 'H':
      humidity = stringToLong(getData()) / 10.0;
      break;
    case 'L':
      lightmeter = stringToLong(getData());
      break;
    case 'R':
      israin = stringToLong(getData());
      break;
    case 'A':
      airdust = stringToLong(getData());
      break;
    case 'U':
      adc_value = stringToLong(getData());
      break;
    case 'Q':
      Serial.println((long)(dht.readTemperature() * 10));
      break;
    case 'W':
      Serial.println((long)(dht.readHumidity() * 10));
      break;
    case 'E':
      int seconds = stringToLong(getData());
      int minutes = stringToLong(getData());
      int hours = stringToLong(getData());
      int dayofweek = stringToLong(getData());
      int dayofmonth = stringToLong(getData());
      int months = stringToLong(getData());
      int years = stringToLong(getData());
      myRTC.setDS1302Time(seconds, minutes, hours, dayofweek, dayofmonth, months, years);
      break;
  }
  //myRTC.setDS1302Time(10, 39, 8, 5, 15, 1, 2016);
  showDataLCD();
  lcdloc();

  /*else if (getWord == "Adj_time\r") {
    Serial.println("OK");

  }*/

  myRTC.updateTime();
  RTCtime();
}
long stringToLong(String s)
{
  char arr[12];
  s.toCharArray(arr, sizeof(arr));
  return atol(arr);
}

String getData(void)
{
  char numberString[10];
  unsigned char index = 0;
  String returnString = "";
  delay(10);
  while (Serial.available() > 0)
  {
    char Serial_Buff = Serial.read();
    if (Serial_Buff == '\r' || Serial_Buff == '\n')
      break;
    else
      returnString += Serial_Buff;
    /*
    delay(10);
    numberString[index++] = Serial.read();
    if (index > 10)
    {
      break;
    }
    }

    numberString[index] = 0;*/
  }
  return returnString;
}

void lcdloc() {

  lcd.setCursor(0, 0);
  lcd.print("TMP:");

  lcd.setCursor(9, 0);
  lcd.print("C ");

  lcd.setCursor(0, 1);
  lcd.print("HUM:");

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

void showDataLCD() {
  //temperature
  lcd.setCursor(4, 0);
  lcd.print(temperature, 1);
  //humidity
  lcd.setCursor(4, 1);
  lcd.print(humidity, 1);
  //還沒調整 rain
  lcd.setCursor(17, 0);
  if (israin == 1)
    lcd.print("T");
  else
    lcd.print("F");
  //airdust
  if (airdust < 1000) {
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
  lcd.setCursor(0, 3);
  lcd.print(myRTC.year);
  lcd.setCursor(4, 3);
  lcd.print("/");

  if (myRTC.month < 10) {
    lcd.setCursor(5, 3);
    lcd.print("0");
    lcd.setCursor(6, 3);
    lcd.print(myRTC.month);
  } else {
    lcd.setCursor(5, 3);
    lcd.print(myRTC.month);
  }

  lcd.setCursor(7, 3);
  lcd.print("/");

  if (myRTC.dayofmonth < 10) {
    lcd.setCursor(8, 3);
    lcd.print("0");
    lcd.setCursor(9, 3);
    lcd.print(myRTC.dayofmonth);
  } else {
    lcd.setCursor(8, 3);
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
  //  lcd.setCursor(0, 3);
  //  weeks();
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
