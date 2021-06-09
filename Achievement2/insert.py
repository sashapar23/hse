import psycopg2

con = psycopg2.connect(database="sashapar", user="sashapar", password="sashapar", host="127.0.0.1", port="5432")

def sql_insert(con):

    cursorObj = con.cursor()

    cursorObj.execute('INSERT INTO numbers(number) VALUES(10)')

    con.commit()

sql_insert(con)
