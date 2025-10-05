#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 9098
int main(){
    int s=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv={AF_INET,htonl(INADDR_ANY),htons(PORT)}, cli; socklen_t l=sizeof(cli);
    bind(s,(struct sockaddr*)&serv,sizeof(serv));
    char buf[1024]; int n;
    while((n=recvfrom(s,buf,1023,0,(struct sockaddr*)&cli,&l))>0){
        sendto(s,buf,n,0,(struct sockaddr*)&cli,l);
    }
    close(s); return 0;
}
