#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "inputmanager.h"
#include "eventmanager.h"
#include "util.h"
#include "data/group.h"


void makePipe(char ***, int);
int main() {
    int flag;
    char command[1024];
    pthread_t managers[4];

    // Start EventManager; Note that EventManager must be initialized first then anything else
    msh_eventman_init(msh_eventman_instance()->thread_handle = &managers[0]);

    // Start InputManager
    msh_inputman_init(&managers[1]);



    // Hold main thread for program being dead
    main_never_die();
}

void dequeue() {
    msh_queue *commands;
    int i, max = que_count(commands);
    for (i = 0; i < max; i++) {
        void *tmp;
        que_dequeue(commands, &tmp);
        msh_group *group = (msh_group *) tmp;

    }
}

void makePipe(char ***cmd, int psize) {
    int p[2];
    pid_t pid;
    int fd_in = 0;
    while ((*cmd) != NULL) {
        pipe(p);
        pid = fork();
        if (pid == 0) {
            dup2(fd_in, 0);
            if ((*cmd)++ != NULL) dup2(p[1], 1);
            close(p[0]);
            execvp((*cmd)[0], *cmd);
            exit(EXIT_FAILURE);

        } else {
            wait(NULL);
            close(p[1]);
            fd_in = p[0];
            cmd++;
        }
    }
}
