#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define ERROR_CODE -1
#define SUCCESS_CODE 0
#define PRINT_CNT 10
#define THREAD_MSG "routine\n"
#define MAIN_MSG "main\n"

void exitWithFailure(const char *msg, int err){
    errno = err;
    fprintf(stderr, "%s256 : %s256", msg, strerror(errno));
    exit(EXIT_FAILURE);
}

int printLine(size_t print_cnt, const char *str){
    for (size_t i = 0; i < print_cnt; ++i){
        int err = write(STDIN_FILENO, str, strlen(str));
        if (err == ERROR_CODE)
            return ERROR_CODE;
    }

    return SUCCESS_CODE;
}

void *routine(void *data){
    int err = printLine(PRINT_CNT, THREAD_MSG);
    if (err == ERROR_CODE)
        exitWithFailure("routine", errno);

    return NULL;
}

int main(int argc, char **argv){
    pthread_t pid;

    int err = pthread_create(&pid, NULL, routine, NULL);
    if (err != SUCCESS_CODE)
        exitWithFailure("main", err);

    err = printLine(PRINT_CNT, MAIN_MSG);
    if (err == ERROR_CODE)
        exitWithFailure("main", errno);

    pthread_exit((void*)(EXIT_SUCCESS));
}
