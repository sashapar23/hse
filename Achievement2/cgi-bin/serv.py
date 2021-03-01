#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import json
import cgi
import sqlite3

print("""Content-Type: application/json\n""")
form = cgi.FieldStorage() 
a=form.getlist('data')[0]
b=int(a)
c=int(a)-1
d=int(b)+1

con = sqlite3.connect('sqlite_python.db')
cursorObj1 = con.cursor()
cursorObj2 = con.cursor()

cursorObj1.execute('SELECT number FROM numbers WHERE number = %s' %b)
cursorObj2.execute('SELECT number FROM numbers WHERE number = %s' %c)
if b < 0:
    x={"value":'add number > 0'}
    y = json.dumps(x)
    print(y)
elif len(cursorObj1.fetchall())!=0:
    x={"value":'this nubmer is already processed'}
    y = json.dumps(x)
    print(y)
elif len(cursorObj2.fetchall())!=0:
    x={"value":'number one less is already processed'}
    y = json.dumps(x)
    print(y)
else:
    cursorObj1.execute('INSERT INTO numbers(number) VALUES(%s)' %b)
    x={"value":c}
    y = json.dumps(x)
    print(y)
    con.commit()
