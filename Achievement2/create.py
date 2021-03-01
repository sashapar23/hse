import sqlite3

from sqlite3 import Error

def sql_connection():

    try:

        con = sqlite3.connect('sqlite_python.db')

        return con

    except Error:

        print(Error)

def sql_table(con):

    cursorObj = con.cursor()

    cursorObj.execute("CREATE TABLE numbers(number int)")

    con.commit()

con = sql_connection()
sql_table(con)
