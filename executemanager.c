//
// Created by somin on 15. 12. 11.
//

#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "executemanager.h"
#include "eventmanager.h"
#include "Reg.h"

void msh_executeman_execute_pipe(msh_group *pGroup);

void msh_executeman_execute_general(msh_group *pGroup);

void msh_executeman_back_command();

void msh_executeman_init(pthread_t *thread_handle, msh_event e) {
    printf("init");
    int is_created = pthread_create(&thread_handle, NULL, msh_executeman_run, (void *) &e);
    printf("%ld\n", thread_handle);
    assert(is_created == 0);
}

static void msh_executeman_run(msh_event *e) {
    msh_executeman_switch_input_type(*e);
}

void msh_executeman_switch_input_type(msh_event e) {
    msh_group *commands = (msh_group *) e.data;
    printf("back : %d\n", commands->isBack);
    //if (commands->isBack) msh_executeman_back_command();
    if (commands->isPipe) msh_executeman_execute_pipe(commands);
    else msh_executeman_execute_general(commands);
}

void msh_executeman_back_command() {
    msh_event e;
    e.data = (void *) getpid();
    e.event_types = INPUTHAN_BACK_INPUT;
//    msh_executeman_pump_event(e);
}

void msh_executeman_execute_general(msh_group *pGroup) {
    // child : execute command
    if (!fork()) {
        void *command_from_queue;
        que_dequeue(pGroup->command, &command_from_queue);
        char *cmd = (char *) command_from_queue;

        char *arr[1024];
        if (regCommands(cmd, space)) {
            arr[0] = strtok(cmd, " ");

            int i;
            for (i = 1; arr[i] = strtok(NULL, " "); i++) { }
            arr[i] = NULL;
        } else {
            arr[0] = cmd;
            arr[1] = NULL;
        }
        //TODO after execute, event check
        //TODO execute_back check
        execvp(arr[0], arr);
    }
        // parent
    else {
        wait(NULL);
    }
}


void msh_executeman_execute_pipe(msh_group *pGroup) {
    // child : execute command
//    int p[2];
//    int fd_in = 0;
    while (que_count(pGroup->command)) {
        void *command_from_queue;
        que_dequeue(pGroup->command, &command_from_queue);
        char *cmd = (char *) command_from_queue;

        if (!fork()) {
//            dup2(fd_in, 0);

            char *arr[1024];
            //TODO token
//            dup2(p[1], 1);
            if (regCommands(cmd, space)) {
                arr[0] = strtok(cmd, " ");

                int i;
                for (i = 1; arr[i] = strtok(NULL, " "); i++) { }
                arr[i] = NULL;
                printf("reg: %d\n", i);
            } else {
                arr[0] = cmd;
                arr[1] = NULL;
            }

//            close(p[0]);
            execvp(arr[0], arr);

            exit(EXIT_FAILURE);

        } else {
            wait(NULL);
//            close(p[1]);
//            fd_in = p[0];
        }
    }
}

void msh_executeman_pump_event(msh_event e) {
    msh_event *event = (msh_event *)malloc(sizeof(msh_event));
    event->event_types = e.event_types;
    event->data = e.data;
//    msh_eventman_dispatch_event(e);
    //TODO request;
}
