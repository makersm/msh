//
// Created by somin on 15. 12. 9.
//

#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio_ext.h>
#include "inputmanager.h"
#include "Reg.h"
#include "group.h"
#include "eventmanager.h"

void msh_inputman_init(pthread_t *thread_handle) {
    // Start input manager within its own thread
    int is_created = pthread_create(thread_handle, NULL, msh_inputman_run, NULL);
    pthread_join(*thread_handle, 0);
    assert(is_created == 0);
}

static void msh_inputman_run() {
    char *input = msh_inputman_read_input();
    msh_event e = msh_inputman_parse_input(input);
    msh_inputman_pump_event(e);
    free(input);
}

char*msh_inputman_read_input() {
    /**
     * print shell command prompt
     * grab input from user
     */
    char *input = "";
    msh_inputman_prompt();
    scanf("%[^\n]s", input);
    __fpurge(stdin);

    return input;
}

msh_event msh_inputman_parse_input(char *input) {
    msh_event e;
    QUEUE *commands = que_create();

    // split command by ;
    regAndSpiltCommands(input, semi_p, commands);
    // split commands by | and check background
    msh_inputman_set_groups(commands);

    e.data = commands;
    e.event_types = INPUTMAN_PARSE_DONE;
    return e;
}

void msh_inputman_pump_event(msh_event e){
    msh_eventman_send_event(e);
}

void msh_inputman_prompt() {
    char path[1024];
    if (getcwd(path, 1024)) fprintf(stdout, "somin[%s]$", path);
}

void msh_inputman_set_groups(QUEUE *commands) {
    int i, num_commands = que_count(commands);
    for(i = 0; i < num_commands; i++) {
        void *get_command;
        que_dequeue(commands, &get_command);

        char *individual = (char *)get_command;
        QUEUE *tmp = que_create();
        regAndSpiltCommands(individual, pipe_p, tmp);
        printf("tmp : %d\n", que_count(tmp));

        Group *group = groupInit();
        group->command = tmp;
        if(que_count(tmp) > 1) group->isPipe = true;
        group->isBack = regCommands(individual, back_p);

        que_enqueue(commands, group);
    }
    printf("commands : %d\n", que_count(commands));
}
