#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdlib.h>

#define NUM 128
#define PRODUCTSUM 3
#define CONSUMESUM 3

sem_t datasem;//Data semaphore
sem_t blanksem;//Free space semaphore
pthread_mutex_t mutex;//Interlocking
int ring[NUM];//Circular Queue

int index1 = 0;//Producersindex
int index2 = 0;//Consumersindex

void *product(void *arg)
{
    srand((unsigned int)time(NULL));
    int n = *(int*)arg;
    while(1)
    {
        sem_wait(&blanksem);//POperation, minus free resources
        pthread_mutex_lock(&mutex);
        int data = rand()%512 + 1;
        ring[index1] = data;
        printf("%d Producers produce a product：%d\n",n,data);
        ++index1;
        index1 %= NUM;
        sem_post(&datasem);//V operations, plus data resources
        pthread_mutex_unlock(&mutex);
       // sleep(1);
    }
}

void *consume(void *arg)
{

    int n = *(int*)arg;
    while(1)
    {
        sleep(1);
        sem_wait(&datasem);//P-operation, minus data resources
        pthread_mutex_lock(&mutex);
        int data = ring[index2];
        printf("%d Consumers have consumed the product：%d\n",n,data);
        ++index2;
        index2 %= NUM;
        sem_post(&blanksem);//V operation, plus free resources
        pthread_mutex_unlock(&mutex);
    }
}
int main()
{
    pthread_mutex_init(&mutex,NULL);
    pthread_t p[PRODUCTSUM];//Producers
    pthread_t c[CONSUMESUM];//Consumers
    sem_init(&blanksem,0,NUM);//Initialize the number of producer vacancies to NUM
    sem_init(&datasem,0,0);//Consumers for 0
    int  i = 1;
    for(i = 1; i < PRODUCTSUM ; ++i)
    {
        int *d = (int*)malloc(sizeof(int));//i is a local variable, if possible when you pass the i value in
        //Cutting out the time slice will change i, which will affect the value of i.
        *d = i;
        pthread_create(&p[i],NULL,product,(void*)d);
    }
    for(i = 1;i < CONSUMESUM; ++i)
    {
        int *d = (int*)malloc(sizeof(int));
        *d = i;
        pthread_create(&c[i],NULL,consume,(void*)d);
    }
    for(i = 1; i < PRODUCTSUM ;++i)
    {
        pthread_join(p[i],NULL);
    }
    for(i = 1; i < CONSUMESUM ;++i)
    {
        pthread_join(c[i],NULL);
    }
    sem_destroy(&blanksem);
    sem_destroy(&datasem);
    pthread_mutex_destroy(&mutex);
    return 0;
}
