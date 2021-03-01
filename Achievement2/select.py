import sqlite3

con = sqlite3.connect('sqlite_python.db')

def sql_fetch(con):

    cursorObj = con.cursor()

    cursorObj.execute('SELECT * FROM numbers')

    rows = cursorObj.fetchall()

    for row in rows:

        print(row)

sql_fetch(con)
