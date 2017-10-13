#-*- coding: utf-8

import pycuril
import json
import io
import csv
import glob
import os


if os.path.isfile('auth_token.txt')
  f = open('auth_token.txt','r')
  auth_token = f.read()
  f.close()

  if os.path.exists('TmpData') : 
    fitsf = sorted(glob.glob('TmpData/*.csv'),key=lambda f: os.stat(f).st_mtime )    
    
    for mesure_file in fitsf:  
    f = open(mesure_file,'r')

    #検索ファイルからデータ取得
    for line in f:
      line = line.rstrip()
      l = line.split(',')
  
    sensor_time = l[0]
    sensor_id = l[1]
    sensor_temp = l[2]


    #温度データをサーバにPost
    # 正確なURL、ヘッダー判明後に入力すること
    buf = io.BytesIO()
    #options = {'user':{'email':'admin@sakelogger.com','password':'password'}}

    c = pycurl.Curl()
    #c.setopt(pycurl.URL, 'https://sakelogger.com/sign_in.json')
    #c.setopt(pycurl.HTTPHEADER,['Authorization':'Token token ='+ auth_token, 'Content-Type:application/json'])
    c.setopt(pycurl.POST,1)
    c.setopt(pycurl.POSTFIELDS,json.dumps(options))
    c.setopt(pycurl.WRITEDATA,buf)
    c.perform()

    buf = buf.getvalue().decode('UTF-8')
    jsonData = json.loads(buf)        
    f.close()


    #レスポンスを確認しOKだったらファイル削除   
    print 'status:'+ jsonData['status']
    if jsonData['status'] == '200':
      ##os.remove(mesure_file)
    else :
      break

