#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9091
#define CHUNK 1024

int main(){
    int sock=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv;
    socklen_t len=sizeof(serv);
    serv.sin_family=AF_INET; serv.sin_port=htons(PORT);
    inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);
    char filename[256];
    printf("Enter filename to request: ");
    scanf("%s",filename);
    sendto(sock,filename,strlen(filename),0,(struct sockaddr*)&serv,len);
    FILE *fp = fopen("received_"+strrchr(filename,'/')? strrchr(filename,'/')+1:filename,"wb");
    if(!fp) fp=fopen("received_file","wb");
    unsigned int expected=0;
    while(1){
        char packet[CHUNK+4];
        int n = recvfrom(sock,packet,sizeof(packet),0,(struct sockaddr*)&serv,&len);
        if(n<=0) break;
        unsigned int seq; memcpy(&seq,packet,4);
        if(n==4){ // final indicator
            break;
        }
        if(seq==expected){
            fwrite(packet+4,1,n-4,fp);
            // send ack
            sendto(sock,&seq,4,0,(struct sockaddr*)&serv,len);
            expected++;
        } else {
            // resend ack for last received
            unsigned int last = expected? expected-1:0;
            sendto(sock,&last,4,0,(struct sockaddr*)&serv,len);
        }
    }
    fclose(fp); close(sock);
    return 0;
}
