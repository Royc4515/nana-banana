# AI CONTEXT: Reference code from Week 4 lecture, slide 53. Use as template/reference for assignment.

import socket # ייבוא מודול הסוקטים

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # יצירת סוקט TCP עבור הלקוח
dest_ip = '127.0.0.1' # כתובת יעד (localhost)
dest_port = 12345 # פורט יעד
s.connect((dest_ip, dest_port)) # יצירת לחיצת היד (Handshake) מול השרת

# פונקציית הקלט מותאמת ל-Python 3
msg = input("Message to send: ") # קבלת קלט ראשוני מהמשתמש

while not msg == 'quit': # לולאה שרצה כל עוד המשתמש לא מקליד quit
    s.send(msg.encode()) # קידוד המחרוזת ל-bytes ושליחתה לשרת
    data = s.recv(4096) # קבלת תשובת ה-Echo מהשרת
    print("Server sent: ", data.decode()) # הדפסת התשובה לאחר פיענוח
    msg = input("Message to send: ") # בקשת קלט נוסף

s.close() # ניתוק חיבור ה-TCP מול השרת
