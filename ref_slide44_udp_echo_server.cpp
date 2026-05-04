// AI CONTEXT: Reference code from Week 4 lecture, slide 44. Use as template/reference for assignment.
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
    
    // יצירת סוקט: AF_INET ל-IPv4, ו-SOCK_DGRAM המייצג תקשורת UDP
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    
    // הגדרת הכתובת והפורט אליהם השרת ייקשר
    // INADDR_ANY אומר שהשרת יקבל תעבורה מכל ממשק רשת במכונה
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port); // המרה לסדר הבתים של הרשת (Big Endian)
    
    // קשירת הסוקט לכתובת שהוגדרה לעיל
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding to socket");
    }
    
    // מבנה נתונים לאחסון פרטי הלקוח השולח ומערך תווים (באפר) לקבלת המידע
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];
    
    // קריאה חוסמת לקבלת נתונים מהלקוח. הפונקציה מאכלסת את 'from' בפרטי השולח
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }
    
    // סגירת המחרוזת כראוי ב-C (כדי שלא נדפיס זבל מהזיכרון)
    buffer[bytes] = '\0'; 
    cout << "The client sent: " << buffer << endl;
    
    // שליחת הנתונים שהתקבלו בחזרה לאותה כתובת לקוח
    int sent_bytes = sendto(sock, buffer, bytes, 0, (struct sockaddr *) &from, sizeof(from));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }
    
    // סגירת תהליך התקשורת
    close(sock);
    return 0;
}
