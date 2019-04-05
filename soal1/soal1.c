#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
typedef long long ll;
ll h[10001];
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

ll factorial(int a){
    if(a==0) return 1;
    ll val=1;
    while(a){
        val=val*a;
        a--;
    }
    return val;
}

void *print_m(void *ptr){
    char *msg;
    msg = (char *) ptr;
    printf("%s\n",msg);
}


int main(int argc,char * argv[])
{
    pthread_t tid[argc-1];
    int i;
    char *ptr;
    int holder[argc-1];
    for(i=1;i<argc;i++){
        holder[i-1]=(int)strtol(argv[i],&ptr,10);
    }
    char str[100];
    qsort(holder,argc-1,sizeof(int),compare);
    for(i=0;i<argc-1;i++){
        h[i]=factorial(holder[i]);
        sprintf(str,"%d! = %lld",holder[i],h[i]);
        const char *hsl=str;
        pthread_create(&(tid[i]),NULL,print_m,(void*)hsl);
        pthread_join(tid[i],NULL);
    }
    return 0;
}
