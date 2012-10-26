//Comentario
#include "email.h"
#include <iostream>
#include <netdb.h>         /* gethostbyname  */
#include <netinet/in.h>    /* htons          */
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>

using namespace std;

Email* Email::instance = NULL;

Email::Email() {}

Email::~Email() {}

Email* Email::Instance() {
	if(instance == NULL) {
		instance = new Email();
	}
	return instance;
}

void Email::Release() {
	if(instance) {
		delete instance;
	}
	instance = NULL;
}

void Email::writeSocket(const int sock, const char *str, const char *arg) {
	char buf[4096];

	if(arg != NULL)
		snprintf(buf, sizeof(buf), str, arg);
	else
		snprintf(buf, sizeof(buf), str, NULL);

	send(sock, buf, strlen(buf), 0);
}

int Email::sendmail(const char *from, const char *to, const char *subject, const char *body, const char *hostname, const int port) {
	struct hostent *host;
	struct sockaddr_in saddr_in;
	int sock = 0;
	char buf[256];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	host = gethostbyname(hostname);

	saddr_in.sin_family      = AF_INET;
	saddr_in.sin_port        = htons((u_short)port);
	saddr_in.sin_addr.s_addr = 0;

	memcpy((char*) & (saddr_in.sin_addr), host->h_addr, host->h_length);

	if(connect(sock, (struct sockaddr*)&saddr_in, sizeof(saddr_in)) == -1) {
		return -2;
	}

	writeSocket(sock, "HELO %s\n",       from);    // greeting
	recv(sock, buf, 254, 0);
	printf("\nRec: %s", buf);
	writeSocket(sock, "MAIL FROM: %s\n", from);    // from
	recv(sock, buf, 254, 0);
	printf("\nRec: %s", buf);
	writeSocket(sock, "RCPT TO: %s\n",   to);      // to
	recv(sock, buf, 254, 0);
	printf("\nRec: %s", buf);
	writeSocket(sock, "DATA\n",          NULL);    // begin data
	recv(sock, buf, 254, 0);
	printf("\nRec: %s", buf);

	// next comes mail headers
	writeSocket(sock, "From: %s\n",      from);
	writeSocket(sock, "To: %s\n",        to);
	writeSocket(sock, "Subject: %s\n",   subject);

	writeSocket(sock, "\n",              NULL);

	writeSocket(sock, "%s\n",            body);    // data

	writeSocket(sock, ".\n",             NULL);    // end data
	recv(sock, buf, 254, 0);
	printf("\nRec: %s", buf);
	writeSocket(sock, "QUIT\n",          NULL);    // terminate

	close(sock);

	return 0;
}
