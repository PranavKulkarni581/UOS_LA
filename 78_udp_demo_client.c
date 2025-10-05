#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 9095
int main(){
    int s=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv={AF_INET,0,htons(PORT)}; inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);
    sendto(s,"PING",4,0,(struct sockaddr*)&serv,sizeof(serv));
    char buf[32]; socklen_t l=sizeof(serv); int n=recvfrom(s,buf,31,0,(struct sockaddr*)&serv,&l); buf[n]=0;
    printf("Reply: %s\n",buf); close(s); return 0;
}
