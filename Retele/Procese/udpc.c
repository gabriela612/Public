/*
Un client trimite unui server doua numere.
Serverul va returna clientului suma celor doua numere.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

struct nr_suma {
        uint16_t a, b;
}nr;


int main() {
        int c;
        struct sockaddr_in server;
        uint16_t a, b, suma;
	unsigned int l = sizeof(server);

        c = socket(AF_INET, SOCK_DGRAM, 0);
        if (c < 0) {
                printf("Eroare la crearea socketului client\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(1234);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
	
	uint16_t p = 1;
	sendto(c, &p, sizeof(p) ,0 ,(struct sockaddr*)&server, sizeof(server));
	recvfrom(c, &p, sizeof(p), MSG_WAITALL, (struct sockaddr*)&server, &l);

	
	server.sin_port = htons(p);
	
        printf("a = "); scanf("%hu",&a);
        printf("b = "); scanf("%hu",&b);
        nr.a = htons(a);
        nr.b = htons(b);
	sendto(c, &nr, sizeof(nr) ,0 ,(struct sockaddr*)&server, sizeof(server));
        //sendto(c, &a, sizeof(a) ,0 ,(struct sockaddr*)&server, sizeof(server));
        //sendto(c,&b,sizeof(b), 0, (struct sockaddr*)&server, sizeof(server));
        recvfrom(c, &suma, sizeof(suma), MSG_WAITALL, (struct sockaddr*)&server, &l);
        suma = ntohs(suma);
        printf("a + b = %hu\n", suma);
        close(c);
}
