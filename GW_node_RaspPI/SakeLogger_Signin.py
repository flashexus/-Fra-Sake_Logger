#-*- coding: utf-8

import pycurl
import json
import io
import csv

buf = io.BytesIO()
options = {'user':{'email':'admin@sakelogger.com','password':'password'}}

c = pycurl.Curl()
c.setopt(pycurl.URL, 'https://sakelogger.com/sign_in.json')
c.setopt(pycurl.HTTPHEADER,['Content-Type:application/json'])
c.setopt(pycurl.POST,1)
c.setopt(pycurl.POSTFIELDS,json.dumps(options))
c.setopt(pycurl.WRITEDATA,buf)
c.perform()

buf = buf.getvalue().decode('UTF-8')
jsonData = json.loads(buf)

auth_token =  jsonData['authentication_token'] 
print 'token =' +  auth_token 

f = open('auth_token.txt','w')
f.write(auth_token)
f.close()

