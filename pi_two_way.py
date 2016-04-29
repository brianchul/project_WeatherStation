import urllib
import httplib
import serial

key = '50K4ERTOTXTA8GX4'
ser = serial.Serial('dev/ttyUSB0', 9600, timeout = 1)
ser2 = serial.Serial('dev/ttyISB1', 9600, timeout = 1)
def sendData():
    try:
        ser.write("Start_nano")
        print "Start_nano"
        print ser.readline()
        tmp = int(ser.readline())
        hum = int(ser.readline())
        light = int(ser.readline())
        rain = int(ser.readline())
        airdust = int(ser.readline())
    try:
        ser.write("Start_UNO")
        print "Start_nano"
        print ser.readline()
        ser2.write(tmp)
        ser2.write(hum)
        ser2.write(light)
        ser2.write(rain)
        ser2.write(airdust)
        UNOtmp = ser2.readline()
        UNOhum = ser2.readline()
        
    headers = {"Content-typZZe": "application/x-www-form-urlencoded","Accept": "text/plain"}
    conn = httplib.HTTPConnection("api.thingspeak.com:80")
    try:
        conn.request("POST", "/update", params, headers)
        response = conn.getresponse()
        print response.status
        print response.reason
        data = response.read()
        conn.close()
    except:
        print "connection failed"


        
if __name__ == "__main__":
    while True:
        sendData()
