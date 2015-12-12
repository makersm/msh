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
#include "data/group.h"
#include "eventmanager.h"

void msh_inputman_init(pthread_t *thread_handle) {
    // Start input manager within its own thread
    int is_created = pthread_create(thread_handle, NULL, msh_inputman_run, NULL);
    assert(is_created == 0);
}

static void msh_inputman_run() {
    char *input = msh_inputman_read_input();
    msh_inputman_parse_input(input);
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

void msh_inputman_parse_input(char *input) {
    msh_queue *commands = que_create();

    // split command by ;
    regAndSpiltCommands(input, semi_p, commands);
    // split commands by | and check background
    msh_inputman_set_groups(commands);
}

void msh_inputman_pump_event(msh_event e){
    msh_eventman_request(&e);
}

void msh_inputman_prompt() {
    char path[1024];
    if (getcwd(path, 1024)) fprintf(stdout, "somin[%s]$", path);
}

// not pretty.. ;(
void msh_inputman_set_groups(msh_queue *commands) {
    int i, num_commands = que_count(commands);
    for(i = 0; i < num_commands; i++) {
        void *get_command;
        que_dequeue(commands, &get_command);

        char *individual = (char *)get_command;
        msh_queue *tmp = que_create();
        regAndSpiltCommands(individual, pipe_p, tmp);
//        printf("tmp : %d\n", que_count(tmp));

        msh_group *group = groupInit();
        group->command = tmp;
        if(que_count(tmp) > 1) group->isPipe = true;
        group->isBack = regCommands(individual, back_p);

        msh_event e;
        e.data = (void*)group;
        e.event_types = INPUTMAN_PARSE_DONE;
        msh_inputman_pump_event(e);
    }
//    printf("commands : %d\n", que_count(commands));
}
