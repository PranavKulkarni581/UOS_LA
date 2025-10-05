#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 9094
int main(){
    int s=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv={AF_INET,htonl(INADDR_ANY),htons(PORT)};
    bind(s,(struct sockaddr*)&serv,sizeof(serv));
    listen(s,5);
    printf("TCP demo server listening %d\n",PORT);
    int c=accept(s,NULL,NULL);
    char buf[256]; int n=read(c,buf,255); buf[n]=0; printf("Got: %s\n",buf);
    write(c, "ACK", 3);
    close(c); close(s);
    return 0;
}
