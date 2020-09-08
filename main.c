#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define PRINT_CNT 10
#define THREAD_MSG "routine\n"
#define MAIN_MSG "main\n"

void exitWithFailure(const char *msg, int err){
    errno = err;
    perror(msg);
    exit(EXIT_FAILURE);
}

void *routine(void *data){
    for (int i = 0; i < PRINT_CNT; ++i){
        int err = write(STDIN_FILENO, THREAD_MSG, strlen(THREAD_MSG));
        if (err == -1)
            exitWithFailure("routine", errno);
    }

    return NULL;
}

int main(int argc, char **argv){
    pthread_t pid;

    int err = pthread_create(&pid, NULL, routine, NULL);
    if (err)
        exitWithFailure("main", err);

    /*
    err =  pthread_detach(pid);
    if (err)
        exitWithFailure("main", err);
    */
   
    for (int i = 0; i < PRINT_CNT; ++i){
        int err = write(STDIN_FILENO, MAIN_MSG, strlen(MAIN_MSG));
        if (err == -1)
            exitWithFailure("main", errno);
    }

    pthread_exit((void*)(EXIT_SUCCESS));
}
