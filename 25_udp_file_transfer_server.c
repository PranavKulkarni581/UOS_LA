#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9091
#define CHUNK 1024

int main(){
    int sock=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in serv, cli;
    socklen_t len=sizeof(cli);
    serv.sin_family=AF_INET; serv.sin_addr.s_addr=INADDR_ANY; serv.sin_port=htons(PORT);
    bind(sock,(struct sockaddr*)&serv,sizeof(serv));
    printf("UDP file server on port %d\n",PORT);
    char filename[256];
    int n = recvfrom(sock, filename, sizeof(filename),0,(struct sockaddr*)&cli,&len);
    filename[n]=0;
    FILE *fp=fopen(filename,"rb");
    if(!fp){ perror("fopen"); close(sock); return 1; }
    unsigned int seq=0;
    char buf[CHUNK];
    while(1){
        size_t r=fread(buf,1,CHUNK,fp);
        // packet: [seq (4 bytes)] [data]
        char packet[CHUNK+4];
        memcpy(packet,&seq,4);
        memcpy(packet+4,buf,r);
        sendto(sock,packet,4+r,0,(struct sockaddr*)&cli,len);
        // wait ack
        char ack[4];
        int tries=0;
        while(1){
            fd_set fds; struct timeval tv; FD_ZERO(&fds); FD_SET(sock,&fds); tv.tv_sec=1; tv.tv_usec=0;
            int s=select(sock+1,&fds,NULL,NULL,&tv);
            if(s>0){
                int an = recvfrom(sock,ack,4,0,(struct sockaddr*)&cli,&len);
                unsigned int aseq; memcpy(&aseq,ack,4);
                if(aseq==seq) break;
            } else {
                // timeout resend
                sendto(sock,packet,4+r,0,(struct sockaddr*)&cli,len);
                tries++;
                if(tries>5) { fclose(fp); close(sock); return 1; }
            }
        }
        seq++;
        if(r<CHUNK) break;
    }
    // send final zero-length packet with seq
    unsigned int seq0=seq;
    sendto(sock,&seq0,4,0,(struct sockaddr*)&cli,len);
    fclose(fp); close(sock);
    return 0;
}
