#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <time.h>
/*Нужно создать нить и напечатать время ее работы*/
void* thr_fn(void *arg)
{
sleep(time(0) % 10);
pthread_exit(NULL);
}
int main(){
pthread_t th_id, id;
void *pret;
pthread_create(&th_id, NULL, thr_fn, NULL);
printf("The thread is created\n");
time_t tm_start = time(0);
printf("Wait thread\n");
if (!pthread_join(th_id, &pret))
    printf("Thread %#lx time = %lu\n", th_id, time(0) - tm_start);
else
    fprintf(stderr, "Error of pthread_join\n");
}