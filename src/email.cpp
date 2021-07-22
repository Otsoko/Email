#include "../include/email.h"
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>

namespace libemail {

    Email *Email::instance = nullptr;

    Email::Email() {}

    Email::~Email() {}

    Email *Email::Instance() {
        if (!instance) {
            instance = new Email();
        }
        return instance;
    }

    void Email::Release() {
        delete instance;
        instance = nullptr;
    }

    void Email::writeSocket(const int sock, const char *str, const char *arg) {
        char buf[4096];

        if (arg) {
            snprintf(buf, sizeof(buf), str, arg);
        } else {
            snprintf(buf, sizeof(buf), str, NULL);
        }

        send(sock, buf, strlen(buf), 0);
    }

    int Email::sendmail(
            const char *from,
            std::vector<std::string> recipients,
            const char *subject,
            const char *body,
            const char *hostname,
            const int port) {
        struct hostent *host;
        struct sockaddr_in saddr_in;
        int sock = 0;
        char buf[256];

        sock = socket(AF_INET, SOCK_STREAM, 0);
        host = gethostbyname(hostname);

        saddr_in.sin_family = AF_INET;
        saddr_in.sin_port = htons((u_short) port);
        saddr_in.sin_addr.s_addr = 0;

        memcpy((char *) &(saddr_in.sin_addr), host->h_addr, host->h_length);

        if (connect(sock, (struct sockaddr *) &saddr_in, sizeof(saddr_in)) == -1) {
            return -2;
        }

        writeSocket(sock, "HELO %s\n", from); // greeting
        recv(sock, buf, 254, 0);
        printf("\nRec: %s", buf);
        writeSocket(sock, "MAIL FROM: %s\n", from); // from
        recv(sock, buf, 254, 0);
        printf("\nRec: %s", buf);

        for (auto &recipient : recipients) {
            writeSocket(sock, "RCPT TO: %s\n", recipient.c_str()); // to
            //printf("RCPT TO: %s\n", recipients.at(i).c_str());
            recv(sock, buf, 254, 0);
        }

        printf("\nRec: %s", buf);
        writeSocket(sock, "DATA\n", NULL); // begin data
        recv(sock, buf, 254, 0);
        printf("\nRec: %s", buf);

        // next comes mail headers
        writeSocket(sock, "From: %s\n", from);

        for (auto &recipient : recipients) {
            writeSocket(sock, "To: %s\n", recipient.c_str()); // to
            //printf("To: %s\n", recipients.at(i).c_str());
        }

        writeSocket(sock, "Subject: %s\n", subject);

        writeSocket(sock, "\n", nullptr);

        writeSocket(sock, "%s\n", body); // data

        writeSocket(sock, ".\n", nullptr); // end data
        recv(sock, buf, 254, 0);
        printf("\nRec: %s", buf);
        writeSocket(sock, "QUIT\n", nullptr); // terminate

        close(sock);

        return 0;
    }

} // namespace libemail
