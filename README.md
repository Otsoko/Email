# Email #

Send email in C++ implementing the SMTP protocol.

## How to use ##

```c++
Email *email = Email::Instance();
std::vector<std::string> recipients;
recipients.push_back("recipient1@server.com");
recipients.push_back("recipient2@server.com");

int ret = email->sendmail(
    "from@server.com",                               /* from     */
    recipients,                                      /* to       */
    "Mail subject",                                  /* subject  */
    "Mail body.\n\nCan contain linebreaks.\n\nBye.", /* body     */
    "localhost",                                     /* hostname */
    25                                               /* port     */
);

if (ret != 0)
    std::cerr << "Failed to send mail (code: " << ret << ")" << std::endl;
else
    std::cout << "Mail successfully sent" << std::endl;

email->Release();
```

## Build

To build this project run

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Run

To run this project run

```bash
$ ./app
```

## License

[Apache License 2.0](https://choosealicense.com/licenses/apache-2.0/)
