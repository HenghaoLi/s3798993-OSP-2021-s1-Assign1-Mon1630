#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM 10
#define PRODUCTSUM 5
#define CONSUMESUM 5

sem_t datasem;
sem_t blanksem;
pthread_mutex_t mutex;//mutex
int buckets[NUM];

int index1 = 0;
int index2 = 0;
bool run = true;
void *product(void *arg)
{
    srand((unsigned int)time(NULL));
    int n = *(int*)arg;
    while(run)
    {
        sem_wait(&blanksem);//P operation, minus idle resources
        pthread_mutex_lock(&mutex);
        int data = rand()%100 + 1;
        buckets[index1] = data;
        printf("%d Producers produce a product：%d\n",n,data);
        ++index1;
        index1 %= NUM;
        sem_post(&datasem);//V operations, plus data resources
        pthread_mutex_unlock(&mutex);
        sleep((0+2.0*(rand()%RAND_MAX)/RAND_MAX*(1-0)));
    }
    return NULL;
}

void *consume(void *arg)
{
    int n = *(int*)arg;
    while(run)
    {
        sleep((0+1.0*(rand()%RAND_MAX)/RAND_MAX*(1-0)));
        sem_wait(&datasem);//P operation, minus idle resources
        pthread_mutex_lock(&mutex);
        int data = buckets[index2];
        printf("%d Consumers have consumed the product: %d\n",n,data);
        ++index2;
        index2 %= NUM;
        sem_post(&blanksem);//V operations, plus data resources
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main()
{
    srand((unsigned int)time(NULL));
    pthread_mutex_init(&mutex,NULL);
    pthread_t p[PRODUCTSUM];//Product
    pthread_t c[CONSUMESUM];//consume
    sem_init(&blanksem,0,NUM);//Initialize the number of producer vacancies to NUM
    sem_init(&datasem,0,0);//Consumers for 0
    int  i = 1;
    for(i = 1; i < PRODUCTSUM ; ++i)
    {
        int *d = (int*)malloc(sizeof(int));
        *d = i;
        pthread_create(&p[i],NULL,product,(void*)d);
    }
    for(i = 1;i < CONSUMESUM; ++i)
    {
        int *d = (int*)malloc(sizeof(int));
        *d = i;
        pthread_create(&c[i],NULL,consume,(void*)d);
    }
    sleep(10);
    run = false;
    printf("It's been simulated for ten seconds.\n");
    sem_destroy(&blanksem);
    sem_destroy(&datasem);
    pthread_mutex_destroy(&mutex);
    return 0;
}
