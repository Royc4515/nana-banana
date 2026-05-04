// AI CONTEXT: Reference code from Week 4 lecture, slide 55. Use as template/reference for assignment.

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {
    const int server_port = 5555;
    
    // פתיחת סוקט מסוג SOCK_STREAM המייצג תקשורת אמינה ומבוססת חיבור (TCP)
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    
    // יצירת מבנה הכתובת וקשירתו לסוקט ההאזנה
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    
    // סימון הסוקט ככזה שמיועד להאזנה לחיבורים נכנסים, עם תור של עד 5 בקשות
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }
    
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    
    // חסימת התוכנית עד לקבלת בקשת חיבור מלקוח. מחזיר File Descriptor חדש לשיחה (client_sock)
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");
    }
    
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    
    // קריאת הנתונים שנשלחו על ידי הלקוח אל תוך הבאפר
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        // ערך 0 מוחזר כאשר הלקוח סוגר את החיבור בצורה תקינה
    } else if (read_bytes < 0) {
        // שגיאה בתהליך הקריאה
    } else {
        buffer[read_bytes] = '\0'; // מניעת הדפסת זבל מזיכרון ישן
        cout << buffer << endl;
    }
    
    // שליחת המידע שנאסף בחזרה ללקוח על גבי הסוקט הייעודי
    int sent_bytes = send(client_sock, buffer, read_bytes, 0);
    if (sent_bytes < 0) {
        perror("error sending to client");
    }
    
    // סגירת הסוקטים
    close(client_sock);
    close(sock);
    return 0;
}
