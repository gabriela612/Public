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
        struct sockaddr_in server, client, copil;
        uint16_t a, b, suma, p;
	int port = 1234;

        int s = socket(AF_INET, SOCK_DGRAM, 0);
        if (s < 0) {
                printf("Eroare la crearea socketului server\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(port);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;

        if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
                printf("Eroare la bind\n");
                return 1;
        }

        unsigned int l = sizeof(client);
        memset(&client, 0, sizeof(client));
	
	while (1) {
	
		port = port + 1;
	
		recvfrom(s, &p, sizeof(p), MSG_WAITALL, (struct sockaddr *) &client, &l);
		sendto(s, &port, sizeof(port), 0, (struct sockaddr *) &client, l);
	
		printf("Un fiu va comunica cu un client pe portul %d\n", port);
	
		if (fork() == 0) {
	
			int sc = socket(AF_INET, SOCK_DGRAM, 0);
	
			memset(&copil, 0, sizeof(copil));
        		copil.sin_port = htons(port);
        		copil.sin_family = AF_INET;
        		copil.sin_addr.s_addr = INADDR_ANY;
	
			if (bind(sc, (struct sockaddr *) &copil, sizeof(copil)) < 0) {
                		printf("Eroare la bind\n");
                		return 1;
        		}
	
			recvfrom(sc, &nr, sizeof(nr), MSG_WAITALL, (struct sockaddr *) &client, &l);
	
        		//recvfrom(sc, &a, sizeof(a), MSG_WAITALL, (struct sockaddr *) &client, &l);
        		//recvfrom(sc, &b, sizeof(b), MSG_WAITALL, (struct sockaddr *) &client, &l);
        		
			a = ntohs(nr.a);
        		b = ntohs(nr.b);
        		suma = a + b;
        		suma = htons(suma);
        		sendto(sc, &suma, sizeof(suma), 0, (struct sockaddr *) &client, l);
        		close(s);
			close(sc);
			return 0;
	
		}
	
	}
}
