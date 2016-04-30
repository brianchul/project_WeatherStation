import urllib
import httplib
import serial
import time

key = '50K4ERTOTXTA8GX4'
ser = serial.Serial('dev/ttyUSB0', 9600, timeout = 1)
ser2 = serial.Serial('dev/ttyUSB1', 9600, timeout = 1)
def sendData():
    try:
        ser.write("Start_nano\r\n")
        print "Start_nano"
        print ser.readline()
        tmp = int(ser.readline())
        hum = int(ser.readline())
        light = int(ser.readline())
        rain = int(ser.readline())
        airdust = int(ser.readline())
    try:
        ser.write("Start_UNO\r\n")
        print "Start_nano"
        print ser.readline()
        ser2.write(tmp)
        ser2.write(hum)
        ser2.write(light)
        ser2.write(rain)
        ser2.write(airdust)
        UNOtmp = ser2.readline()
        UNOhum = ser2.readline()
        
    params = urllib.urlencode({'field1':tmp,'field2':hum,'field3':light,'field4':rain,'field5':airdust,'field6':UNOtmp,'field7':UNOhum,key':key})
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
        time.sleep(15)
