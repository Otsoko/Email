//Comentario
#include <iostream>
#include "email.h"

int main() {
	Email *email = Email::Instance();
	
	int ret = email->sendmail(
        "from@from-host.org",   /* from     */
        "annirbal@gmail.com",       /* to       */
        "Subject",              /* subject  */
        "body",                 /* body     */
        "localhost",             /* hostname */
        25                      /* port     */
    );

    if (ret != 0)
		std::cerr << "Failed to send mail (code: " << ret << ")" << std::endl;
    else
		std::cout << "Mail successfully sent" << std::endl;
	
	email->Release();
	return ret;
}
