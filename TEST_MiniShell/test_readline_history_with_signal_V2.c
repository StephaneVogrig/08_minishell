#include "./libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	handler_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(void)
{
	char				*inpt;
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	signal(SIGINT, handler_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		inpt = readline("Minishell >");
		if (!inpt)
			exit(1);
		if (inpt[0] != '\0')
			add_history(inpt);
		printf("%s", inpt);
		printf("\n");
		if (ft_strncmp("exit", inpt, 4) == 0)
		{
			free(inpt);
			exit(1);
		}
	}
}
