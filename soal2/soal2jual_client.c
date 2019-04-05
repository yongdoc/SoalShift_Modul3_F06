#include <stdio.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 7001

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    key_t key = 1799;
    char a[100];
    while(1){
        int *value;
        int stok=shmget(key,sizeof(int),IPC_CREAT|0666);
        value = shmat(stok,NULL,0);
        char buffer[1024]={0};
        gets(a);
        send(sock , a , strlen(a) , 0 );
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer);
    }
    return 0;
}