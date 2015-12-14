//
// Created by somin on 15. 12. 9.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio_ext.h>
#include "inputhandler.h"
#include "Reg.h"
#include "data/group.h"
#include "eventmanager.h"

void msh_inputhan_run() {
    char *input = msh_inputhan_read_input();
    msh_inputhan_parse_input(input);
}

char* msh_inputhan_read_input() {
    /**
     * print shell command prompt
     * grab input from user
     */
    char input[1024];
    msh_inputhan_prompt();
    scanf("%[^\n]s", input);
    __fpurge(stdin);
    return input;
}

void msh_inputhan_parse_input(char *input) {
    msh_queue *commands = que_create();

    // split command by ;
    regAndSpiltCommands(input, semi_p, commands);

    // split commands by | and check background
    msh_inputhan_set_groups(commands);
}

void msh_inputhan_pump_event(msh_event e){
    msh_event *event = (msh_event *)malloc(sizeof(msh_event));
    event->event_types = e.event_types;
    event->data = e.data;
    msh_eventman_request(event);
}

void msh_inputhan_prompt() {
    char path[1024];
    if (getcwd(path, 1024)) fprintf(stdout, "somin[%s]$", path);
}

// not pretty.. ;(
void msh_inputhan_set_groups(msh_queue *commands) {
    int i, num_commands = que_count(commands);

    for(i = 0; i < num_commands; i++) {
        void *get_command;
        que_dequeue(commands, &get_command);

        char *individual = (char *)get_command;
        msh_queue *tmp = que_create();
        regAndSpiltCommands(individual, pipe_p, tmp);

        msh_group *group = groupInit();
        group->command = tmp;
        if(que_count(tmp) > 1) group->isPipe = true;
        else group->isPipe = false;
        group->isBack = regCommands(individual, back_p);

        msh_event e;
        e.data = (void*)group;
        e.event_types = INPUTHAN_PARSE_DONE;
        msh_inputhan_pump_event(e);
    }
}
