#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 9094
int main(){
    int s=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv={AF_INET,0,htons(PORT)};
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);
    connect(s,(struct sockaddr*)&serv,sizeof(serv));
    write(s,"Hello TCP",9);
    char buf[32]; int n=read(s,buf,31); buf[n]=0; printf("Reply: %s\n",buf);
    close(s); return 0;
}
