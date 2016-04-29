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
