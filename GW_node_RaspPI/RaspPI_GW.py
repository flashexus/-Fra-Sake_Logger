#coding:UTF-8

import csv
import serial
import time
from datetime import datetime

 #-------------------------------------------
def exit_handler(signal,frame):
  #Ctrl+C Action
  print("\nExit")
  ser.close()
  f.close()
  sys.exit(0)

#-------------------------------------------
ser = serial.Serial('/dev/ttyACM0',9600)
listData = []

#-------------------------------------------
while True:
  if ser.inWaiting() > 0 :
    string  = ser.readline()  
    header_idx = string.rfind("AAAA")
    if header_idx != -1 :

      string_time = datetime.now().strftime("%Y_%m_%d_%H:%M:%S")
      file_path = "TmpData/TmpData" +string_time + ".csv"  
      f = open(file_path,'ab')
      csvWriter = csv.writer( f )

      string = string[header_idx + 4:]
      string = string.strip("\r\n")
      Node_ID = string[-4:]
      Tmp_Data =string[:-4]

      listData.append(string_time)
      listData.append(Node_ID)
      listData.append(Tmp_Data)
      csvWriter.writerow(listData)
      listData = []
    else:
      Node_ID = "Error" 
      Tmp_Data = "Error"
      string_time = "Error"

#------------------------------------------
    print("Time:" + str(string_time))
    print("Node_ID:" + Node_ID)
    print("Tmp_Data:" + Tmp_Data)

    time.sleep(1)
