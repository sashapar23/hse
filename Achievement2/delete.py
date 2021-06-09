import psycopg2

con = psycopg2.connect(database="sashapar", user="sashapar", password="sashapar", host="127.0.0.1", port="5432")

def sql_fetch(con):

    cursorObj = con.cursor()

    cursorObj.execute('DROP table if exists numbers')

    con.commit()

sql_fetch(con)
con.close()
