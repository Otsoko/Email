# Email #

Send email in C++ implementing the SMTP protocol.

## How to use ##

```c++
#include <iostream>
#include <vector>
#include "../include/email.h"

using libemail::Email;

int main() {
    Email *email = Email::Instance();
    std::vector<std::string> recipients;
    recipients.push_back("pepe@mailinator.com");
    recipients.push_back("pepa@mailinator.com");
    
    int ret = email->sendmail(
    "hola@hotmail.com",                              /* from     */
    recipients,                                      /* to       */
    "Mail subject",                                  /* subject  */
    "Mail body.\n\nCan contain linebreaks.\n\nBye.", /* body     */
    "localhost",                                     /* hostname */
    25                                               /* port     */
    );
    
    if (ret != 0) {
    std::cerr << "Failed to send mail (code: " << ret << ")" << std::endl;
    } else {
    std::cout << "Mail successfully sent" << std::endl;
    }
    
    email->Release();
    
    return ret;
}

```
