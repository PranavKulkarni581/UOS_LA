#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 9095
int main(){
    int s=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv={AF_INET,htonl(INADDR_ANY),htons(PORT)}, cli; socklen_t l=sizeof(cli);
    bind(s,(struct sockaddr*)&serv,sizeof(serv));
    char buf[256]; int n=recvfrom(s,buf,255,0,(struct sockaddr*)&cli,&l); buf[n]=0;
    printf("UDP got: %s\n",buf);
    sendto(s,"PONG",4,0,(struct sockaddr*)&cli,l);
    close(s); return 0;
}
