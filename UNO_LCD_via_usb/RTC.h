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
