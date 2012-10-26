#ifndef EMAIL_H
#define EMAIL_H

class Email {

	static Email* instance;

public:
	static Email* Instance();
	static void Release();
	int sendmail(const char *from, const char *to, const char *subject, const char *body, const char *hostname, const int port);

private:
	Email();
	virtual ~Email();
	void writeSocket(const int sock, const char *str, const char *arg);
};

#endif // EMAIL_H
