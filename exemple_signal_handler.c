/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exemple_signal_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:06:52 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/17 21:16:14 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
find on stackoverflow at :
https://stackoverflow.com/questions/53165704/readline-c-force-return-of-certain-text-in-readline
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

static volatile sig_atomic_t my_signal_flag = 0;
static int done_loop = 0;

void my_signal_handler (int status)
{
   my_signal_flag = 1;                       // set a volaatile sig-atomic_t var
                                             // and exit, just as the standard says
}

void my_rlhandler(char* line)                // all your app is in this function
                                             // called each time a line is ready
{
    if (line && strcmp(line, "quit"))
        printf("Entry was: %s\n", line);
    else
    {
       done_loop = 1;
       rl_set_prompt("");
    }
    free(line);
}

void my_event_loop()                         // event loop
                                             // handle all async events here
                                             // signals, network, threads, whatever
{
    rl_callback_handler_install("w00t>", my_rlhandler);

    do
    {
        signal(SIGINT, my_signal_handler);   // readline may override this
                                             // better do it here each time
        fd_set readfds;                      // prepare the select
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);

        if (select(1, &readfds, NULL, NULL, NULL) > 0)
        {
            rl_callback_read_char();         // character ready, let readline eat it
        }
        else if (my_signal_flag )
        {
            my_signal_flag = 0;              // can get here only after a signal
            rl_replace_line("word",0);      
            rl_done = 1;
            rl_redisplay();
            rl_pending_input = '\n';         // not sure why it's needed
            rl_callback_read_char();
        }
    }
    while (!done_loop);

    rl_callback_handler_remove();
}


int main (int argc, char** argv)
{
    char* entry;
    signal(SIGINT, my_signal_handler);

    my_event_loop();

    return 0;
}