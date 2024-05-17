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

void	handler_ctrl_c_interactive(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// print_prompt();
	}
}

// void	handler_ctrl_c(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		write(1, "\n", 2);
// 		print_prompt();
// 	}
// }

// void	handler_ctrl_backslash(int signal)
// {
// 	if (signal == SIGQUIT)
// 	{
// 		// write(1, "\n", 2);
// 		print_prompt();
// 	}
// }

/// Pour [ctr + d]
//->Si dans here_doc et rien ecrit retourne message d'erreur suivant:
//     bash: warning: here-document at line 14 delimited by end-of-file (wanted `limiter')
// faire [ctr + d] dans le here_doc c'est comme entrer le limiter

int	main(void)
{
	char				*inpt;
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	// sa.sa_sigaction = handler_ctrl_c;
	// sa.sa_flags = SA_SIGINFO;
	// sigaction(SIGINT, &sa, NULL);
	signal(SIGINT, handler_ctrl_c_interactive);
	// signal(SIGQUIT, handler_ctrl_backslash);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		// print_prompt();
		inpt = readline("Minishell >");
		if (!inpt) /// pour ctrl+d
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
