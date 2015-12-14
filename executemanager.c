//
// Created by somin on 15. 12. 11.
//

#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "executemanager.h"
#include "eventmanager.h"
#include "Reg.h"
#include "util.h"

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
    e.data = (void *) pthread_self();
    e.event_types = INPUTHAN_BACK_INPUT;
//    msh_executeman_pump_event(e);
}

void msh_executeman_execute_general(msh_group *pGroup) {
    // child : execute command
    if (!fork()) {
        void *command_from_queue;
        que_dequeue(pGroup->command, &command_from_queue);
        char *cmd = (char *) command_from_queue;
        char *ary[1024];
        msh_queue queue_arr;
        regAndSpiltCommands(cmd, space, &queue_arr);
        int i;
        for(i = 0; !que_count(&queue_arr); i++) {
            void *tmp;
            ary[i] = (char *)que_dequeue(&queue_arr, &tmp);

        }
//        if (regCommands(cmd, space)) {
//            arr[0] = strtok(cmd, " ");
//
//            int i;
//            for (i = 1; arr[i] = strtok(NULL, " "); i++) { }
//            arr[i] = NULL;
//        } else {
//            arr[0] = cmd;
//            arr[1] = NULL;
//        }
        //TODO after execute, event check
        //TODO execute_back check
//        execvp(queue_arr[0], queue_arr);
    }
        // parent
    else {
        wait(NULL);
    }
}


void msh_executeman_execute_pipe(msh_group *pGroup) {
    // child : execute command
    char *fifo_name = msh_util_time_stamp();
    mkfifo(fifo_name, 0666);

    int fd;
    fd = open(fifo_name, O_RDWR);

    int i, pipe_size = que_count(pGroup->command);
    for(i = 0; i < pipe_size; i++) {
        void *command_from_queue;
        que_dequeue(pGroup->command, &command_from_queue);
        char *cmd = (char *) command_from_queue;

        int pid = fork();
        if (pid == 0) {
            dup2(fd, 0);

            if(i != pipe_size-1) {
                dup2(fd, 1);
            }

            msh_queue queue_arr;
            regAndSpiltCommands(cmd, space, &queue_arr);

            char *ary[1024];
            int j, max = que_count(&queue_arr);
//            printf("max: %d\n", max);
            for(j = 0; j < max; j++) {
                void *tmp;
                que_dequeue(&queue_arr, &tmp);
                ary[j] = (char*)tmp;
                printf("arr%d: %s\n", j, ary[j]);
            }
            ary[j] = NULL;

            execvp(ary[0], ary);
//            memset(ary, 0, 1024);
            exit(0);

        } else {
            wait(NULL);
            printf("count: %d\n", i);
        }
    }
    printf("hellp");
}

void msh_executeman_pump_event(msh_event e) {
    msh_event *event = (msh_event *)malloc(sizeof(msh_event));
    event->event_types = e.event_types;
    event->data = e.data;
//    msh_eventman_dispatch_event(e);
    //TODO request;
}
