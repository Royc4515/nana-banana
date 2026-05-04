# AI CONTEXT: Reference code from Week 4 lecture, slide 51. Use as template/reference for assignment.

import socket # ייבוא מודול הסוקטים

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # יצירת סוקט TCP (מיוצג על ידי SOCK_STREAM)
server_ip = '' # האזנה לכל הכתובות המקומיות
server_port = 12345 # קביעת פורט ההאזנה
server.bind((server_ip, server_port)) # קשירת הסוקט לכתובת
server.listen(5) # כניסה למצב האזנה, עם תור המתנה מקסימלי של 5 לקוחות

while True: # לולאה שמקבלת לקוחות חדשים
    client_socket, client_address = server.accept() # קריאה חוסמת לאישור חיבור חדש, מחזירה סוקט נפרד לשיחה
    print('Connection from: ', client_address) # הדפסת פרטי הלקוח
    data = client_socket.recv(1024) # קבלת נתונים ראשונית מהלקוח

    while not data == b'': # כל עוד החיבור פעיל והלקוח לא סגר אותו (שליחת מחרוזת ריקה משמעותה ניתוק)
        print('Received: ', data.decode()) # הדפסת המידע שהתקבל
        client_socket.send(data.upper()) # הדהוד המידע חזרה באותיות גדולות
        data = client_socket.recv(1024) # קריאת נתונים נוספים בלולאה

    print('Client disconnected') # ברגע שהלולאה הפנימית נשברת, הלקוח התנתק
    client_socket.close() # סגירת הסוקט הייעודי מול הלקוח הנוכחי
