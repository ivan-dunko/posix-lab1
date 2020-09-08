#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define PRINT_CNT 10
#define THREAD_MSG "routine\n"
#define MAIN_MSG "main\n"

void exitWithFailure(const char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void *routine(void *data){
    for (int i = 0; i < PRINT_CNT; ++i)
        if (write(STDIN_FILENO, THREAD_MSG, strlen(THREAD_MSG)) == -1)
            exitWithFailure("routine");

	return NULL;
}

int main(int argc, char **argv){
    pthread_t pid;

    if ((errno = pthread_create(&pid, NULL, routine, NULL) == -1)
#ifndef LAB2
        || (errno = pthread_detach(pid) == -1)
#endif
                                            )
        exitWithFailure("main");

#ifdef LAB2
    if (errno = pthread_join(pid, NULL) == -1)
        exitWithFailure("main");
#endif

    for (int i = 0; i < PRINT_CNT; ++i)
        if (write(STDIN_FILENO, MAIN_MSG, strlen(MAIN_MSG)) == -1)
            exitWithFailure("main");

    pthread_exit((void*)(EXIT_SUCCESS));
}
