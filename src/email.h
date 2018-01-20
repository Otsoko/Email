#ifndef EMAIL_H
#define EMAIL_H

#include <iostream>
#include <vector>

class Email {

	static Email* instance;

public:
	static Email* Instance();
	static void Release();
	int sendmail(const char *from, std::vector<std::string> recipients, const char *subject, const char *body, const char *hostname, const int port);

private:
	Email();
	virtual ~Email();
	void writeSocket(const int sock, const char *str, const char *arg);
};

#endif // EMAIL_H