import sqlite3

con = sqlite3.connect('sqlite_python.db')

def sql_insert(con):

    cursorObj = con.cursor()

    cursorObj.execute('INSERT INTO numbers(number) VALUES(10)')

    con.commit()

sql_insert(con)
