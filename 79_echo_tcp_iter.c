#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 9096
int main(){
    int s=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv={AF_INET,htonl(INADDR_ANY),htons(PORT)};
    bind(s,(struct sockaddr*)&serv,sizeof(serv));
    listen(s,5);
    int c=accept(s,NULL,NULL);
    char buf[512]; int n;
    while((n=read(c,buf,511))>0){ write(c,buf,n); }
    close(c); close(s); return 0;
}
