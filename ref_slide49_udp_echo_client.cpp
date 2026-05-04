// AI CONTEXT: Reference code from Week 4 lecture, slide 49. Use as template/reference for assignment.

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {
    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;
    
    // אתחול סוקט הלקוח עבור פרוטוקול UDP (SOCK_DGRAM)
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    
    // הגדרת הכתובת של שרת היעד שאליו נשלח את הבקשה
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address); // המרת ה-IP ממחרוזת למבנה בינארי שמתאים לרשת
    sin.sin_port = htons(port_no);
    
    // הכנת המידע לשליחה והפעלת פונקציית השליחה מול כתובת השרת
    char data[] = "hello";
    int data_len = sizeof(data);
    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }
    
    // המתנה לקבלת התשובה חזרה מהשרת
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }
    
    // טיפול בהדפסת התשובה וסגירת הסוקט
    buffer[bytes] = '\0';
    cout << "The server sent: " << buffer << endl;
    
    close(sock);
    return 0;
}
