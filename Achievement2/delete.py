import sqlite3

con = sqlite3.connect('sqlite_python.db')

def sql_fetch(con):

    cursorObj = con.cursor()

    cursorObj.execute('DROP table if exists numbers')

    con.commit()

sql_fetch(con)
