import psycopg2

def sql_connection():

    try:

        con = psycopg2.connect(database="sashapar", user="sashapar", password="sashapar", host="127.0.0.1", port="5432")

        return con

    except:

        print("Error")

def sql_table(con):

    cursorObj = con.cursor()

    cursorObj.execute("CREATE TABLE numbers(number int)")

    con.commit()

con = sql_connection()
sql_table(con)
