#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void* p1(void *arg);
void* p2(void *arg);
void* p3(void *arg);
int status;
int main(){
    pthread_t tid[3];
    int i;
    pthread_create(&(tid[0]),NULL,&p1,NULL);
    pthread_create(&(tid[1]),NULL,&p2,NULL);
    pthread_create(&(tid[2]),NULL,&p3,NULL);
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    return 0;
}

void *p1(void *arg)
{
    status = 0;
    system("ps -aux | awk 'NR<=11 {print}' > /home/yong/Documents/FolderProses1/SimpanProses1.txt");
    system("ps -aux | awk 'NR<=11 {print}' > /home/yong/Documents/FolderProses2/SimpanProses2.txt");
    printf("Proses penyimpanan pada file berhasil\n");
    status++;
    return NULL;
}

void *p2(void *arg)
{
    while(status < 1);
    system("cd /home/yong/Documents/FolderProses1;zip KompresProses1.zip SimpanProses1.txt");
    system("cd /home/yong/Documents/FolderProses2;zip KompresProses2.zip SimpanProses2.txt");
    system("rm /home/yong/Documents/FolderProses1/SimpanProses1.txt");
    system("rm /home/yong/Documents/FolderProses2/SimpanProses2.txt");
    printf("Menunggu 15 detik untuk mengekstrak kembali\n");
    sleep(15);
    status++;
    return NULL;
}

void *p3(void *arg)
{
    while(status!=2);
    system("cd /home/yong/Documents/FolderProses1;unzip KompresProses1.zip");
    system("cd /home/yong/Documents/FolderProses2;unzip KompresProses2.zip");
    printf("File berhasil di ekstrak\n");
}
