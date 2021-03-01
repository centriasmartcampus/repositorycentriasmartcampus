//#include <QCoreApplication>

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    return a.exec();
//}

#include <string>
#include "fcgi_stdio.h"
#include <stdlib.h>
#include <iostream>

void handle(FCGX_Request request){
FCGX_FPrintF(request.out, "Content-type: text/html\r\n\r\n<TITLE>fastcgi</TITLE>\n<H1>Fastcgi:.</H1>\n");
}

int main(int argc, char* const argv[] )
{

std::string port=":9001";
int listenQueueBacklog = 400;
FCGX_Stream *in, *out, *err;
FCGX_ParamArray envp;


if(FCGX_Init()) exit(1);

int listen_socket = FCGX_OpenSocket(port.c_str(), listenQueueBacklog);
if(listen_socket < 0) exit(1);

FCGX_Request request;
if(FCGX_InitRequest(&request, listen_socket, 0)) exit(1);

int reqCounter = 0;
while(FCGX_Accept_r(&request) == 0)
{
//handle(request);
//FCGX_FPrintF(request.out, "Content-type: text/html\r\n\r\n<TITLE>fastcgi</TITLE>\n<H1>Fastcgi: Hello world.</H1>\n");
reqCounter++;
FCGX_FPrintF(request.out, "\n\r\n\r counter: %d", reqCounter);

//FCGX_Finish_r(&request);
}

return 0;
}
