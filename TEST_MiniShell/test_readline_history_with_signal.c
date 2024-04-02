#include "./libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	print_prompt(void)
{
	write(1, "minishell> ", 11);
}

// void	handler_ctrl_c(int signal, siginfo_t *info, void *context)
// {
// 	info = (void *)info;
// 	context = (void *)context;
// 	if (signal == SIGINT)
// 	{
// 		write(1, "\n", 3);
// 		print_prompt();
// 	}
// }

void	handler_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 2);
		print_prompt();
	}
}

// void	handler_ctrl_backslash(int signal)
// {
// 	if (signal == SIGQUIT)
// 	{
// 		// write(1, "\n", 2);
// 		print_prompt();
// 	}
// }

int	main(void)
{
	char				*inpt;
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	// sa.sa_sigaction = handler_ctrl_c;
	// sa.sa_flags = SA_SIGINFO;
	// sigaction(SIGINT, &sa, NULL);
	signal(SIGINT, handler_ctrl_c);
	// signal(SIGQUIT, handler_ctrl_backslash);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		print_prompt();
		inpt = readline("");
		if (!inpt) /// pour ctrl+d
			exit(1);
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
