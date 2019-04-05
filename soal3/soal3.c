#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

int wakestat=0,sprtstat=100,trigger=0,counter1=1,counter2=1;
void *bangun(void *arg);
void *tidur(void *arg);

int main()
{
    pthread_t tid[2];
    char a[100];
    pthread_create(&(tid[0]),NULL,&bangun,NULL);
    pthread_create(&(tid[1]),NULL,&tidur,NULL);
    while(1){
        gets(a);
        if(!strcmp(a,"Agmal Ayo Bangun")){
            trigger=1;
        }else if(!strcmp(a,"Iraj Ayo Tidur")){
            trigger=2;
        }else if(!strcmp(a,"All Status")){
            printf("Agmal WakeUp_Status = %d\nIraj Spirit_Status = %d\n",wakestat,sprtstat);
        }else {
            printf("tidak terdapat perintah tersebut\n");
        }
        if(wakestat>=100){
            printf("Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
            break;
        }else if(sprtstat<=0){
            printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
            break;
        }
    }
    return 0;
}

void *bangun(void *arg){
    while(1){
        if(trigger==1){
            if(!(counter1%4)){
                counter1=1;
                trigger=0;
                sleep(10);
                return NULL;
            }
            counter2++;
            wakestat+=15;
            trigger=0;
            if(!(counter2%4)){
                printf("Iraj Ayo Tidur is disabled 10 s\n");
            }
        }
    }
}
void *tidur(void *arg){
    while(1){
        if(trigger==2){
            if(!(counter2%4)){
                counter2=1;
                trigger=0;
                sleep(10);
                continue;
            }
            counter1++;
            sprtstat-=20;
            trigger=0;
            if(!(counter1%4)){
                printf("Agmal Ayo Bangun is disabled 10 s\n");
            }
        }
    }
}
