FROM python:3

WORKDIR /usr/src/app

COPY requirements.txt ./
RUN pip3 install --no-cache-dir psycopg2 && pip3 install --no-cache-dir python-dotenv

COPY hellow.py .

ENTRYPOINT [ "sh", "./entrypoint.sh" ]
