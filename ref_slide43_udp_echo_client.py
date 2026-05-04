from socket import socket, AF_INET, SOCK_DGRAM # ייבוא האובייקטים ליצירת תקשורת UDP מעל IPv4

s = socket(AF_INET, SOCK_DGRAM) # אתחול אובייקט סוקט UDP עבור הלקוח
dst_ip = '127.0.0.1' # כתובת ה-IP של השרת - כאן מוגדר Localhost (המכונה המקומית)
dst_port = 12345 # הפורט עליו מאזין השרת

# שים לב: בפייתון 3 חובה לשלוח מחרוזות כ-bytes, ולכן נוספה הקידומת 'b'
s.sendto(b'Hello', (dst_ip, dst_port)) # שליחת חבילת נתונים (Datagram) עם המחרוזת לשרת
data, sender_info = s.recvfrom(2048) # המתנה לקבלת התשובה מהשרת, עד 2048 בתים

print("Server sent:", data.decode()) # הדפסת התשובה שהתקבלה מהשרת (תוספת קטנה לוודא שעובד)
s.close() # סגירת הסוקט ושחרור משאבי מערכת ההפעלה
