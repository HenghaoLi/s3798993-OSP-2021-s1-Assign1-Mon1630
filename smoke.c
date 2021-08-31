#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
sem_t offer1;
sem_t offer2;
sem_t offer3;
sem_t finish;

int sequence;

void* Agent_process(void* arg)
{
    printf("Agent_process\n");
    while(1)
    {
        srand(time(0));
        sequence = rand() % 3;
        if(sequence == 0)
        {
            sem_post(&offer1);
            printf("Agent provides tobacco and paper\n");
        }
        else if (sequence == 1)
        {
            sem_post(&offer2);
            printf("Agent provides tobacco and matches\n");
        }
        else
        {
            sem_post(&offer3);
            printf("Agent provides paper and matches\n");
        }
        printf("The agent is waiting for the smoker to finish smoking\n");
        sem_wait(&finish);
        printf("Finish\n\n");
    }
}

void* smoker_process_one(void* arg)
{
    printf("smoker_process_one\n");
    while(1)
    {
        sem_wait(&offer3);
        printf("The first smoker had tobacco, took the paper and matches given by the agent and began to smoke\n");
        sleep(1);
        sem_post(&finish);
    }
}

void* smoker_process_two(void* arg)
{
    printf("smoker_process_two\n");
    while(1)
    {
        sem_wait(&offer2);
        printf("The second smoker had papper, took the tobacco and matches given by the agent and began to smoke\n");
        sleep(1);
        sem_post(&finish);
    }
}

void* smoker_process_three(void* arg)
{
    printf("smoker_process_three\n");
    while(1)
    {
        sem_wait(&offer1);
        printf("The third smoker had matches, took the tobacco and papper given by the agent and began to smoke\n");
        sleep(1);
        sem_post(&finish);
    }
}

int main()
{
    sem_init(&offer1, 0, 0);
    sem_init(&offer2, 0, 0);
    sem_init(&offer3, 0, 0);
    sem_init(&finish, 0, 0);

    pthread_t supple;
    pthread_t smoker[3];
    
    pthread_create(&supple, NULL, Agent_process, NULL);
    
    pthread_create(&smoker[0], NULL, smoker_process_one, NULL);
    pthread_create(&smoker[1], NULL, smoker_process_two, NULL);
    pthread_create(&smoker[2], NULL, smoker_process_three, NULL);
    
    sleep(10);  
    printf("\n\nIt's been simulated for ten seconds.\n");

    sem_destroy(&offer1);
    sem_destroy(&offer2);
    sem_destroy(&offer3);
    sem_destroy(&finish);
    return 0;
}
