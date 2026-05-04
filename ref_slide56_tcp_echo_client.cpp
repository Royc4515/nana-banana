// AI CONTEXT: Reference code from Week 4 lecture, slide 56. Use as template/reference for assignment.

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
    
    // יצירת הסוקט בצד הלקוח (TCP)
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    
    // הגדרת היעד להתחברות
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);
    
    // הפעלת לחיצת יד של TCP מול השרת
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
    
    // הגדרת המחרוזת לשליחה וחישוב האורך שלה
    char data_addr[] = "Im a message";
    int data_len = strlen(data_addr);
    
    // שליחת הנתונים לשרת על גבי הזרם
    int sent_bytes = send(sock, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        // טיפול בשגיאת שליחה
    }
    
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    
    // המתנה לתשובה (ההדהוד) מהשרת
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
        // connection is closed
    } else if (read_bytes < 0) {
        // error
    } else {
        buffer[read_bytes] = '\0'; // וידוא סגירה תקינה של המחרוזת
        cout << buffer << endl;
    }
    
    // סיום השיחה וסגירת הסוקט
    close(sock);
    return 0;
}
