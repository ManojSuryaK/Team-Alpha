from Adafruit_IO import *
import time
import serial 
client=Client('8b0e88bd397d4d9cb6f840f111922282')#key to access the dashboard
line=[]
handler=serial.Serial("/dev/ttyACM0",115200)#creating serial data object
while True:
    lineRead=handler.readline()#obtaining serial data from uart
    line=lineRead.split("\t")
    print "got message"#message received
    if line[0]=="s":#soil moisture data
        print "got soil moisture"
        client.send("moisture",int(line[1]))
        print 'moisture sent'
        time.sleep(0.1)
    elif line[0]=="t":#temperature data
        print "got temperature"
        client.send("temperature",float(line[1]))
        print 'temprature sent'
        time.sleep(0.1)
    print "sent"
        
handler.close()
            
    
        
    

