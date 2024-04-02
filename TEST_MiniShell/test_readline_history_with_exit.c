#include "./libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// compiler avec flag -lreadline

void	exit_cmd(char *inpt, char **cmd_lst)
{
	int	exit_val;

	exit_val = 0;
	if (ft_strncmp("exit", inpt, 4) == 0 && !cmd_lst[1])
	{
		ft_free_the_tab(cmd_lst);
		free(inpt);
		exit(exit_val);
		/// !!! exit_val doit prendre la val de derniere erreur du programme-> a voir
	}
	else if (ft_strncmp("exit", inpt, 4) == 0 && !cmd_lst[2])
	{
		if (ft_str_isalpha(cmd_lst[1]) == 0)
			exit_val = ft_atoi(cmd_lst[1]);
		else
		{
			exit_val = 2;
			printf("exit: ");
			printf("%s : ", cmd_lst[1]);
			printf("numeric argument required\n");
		}
		ft_free_the_tab(cmd_lst);
		free(inpt);
		exit(exit_val);
	}
	else if (ft_strncmp("exit", inpt, 4) == 0 && cmd_lst[2])
	{
		printf("exit: ");
		printf("too many arguments\n");
		exit_val = 1;
	}
}

int	main(void)
{
	char	*inpt;
	char	**cmd_lst;

	while (1)
	{
		inpt = readline("Minishell> ");
		add_history(inpt);
		if (inpt)
			cmd_lst = ft_split(inpt, ' ');
		if (ft_strncmp("exit", inpt, 4) == 0)
			exit_cmd(inpt, cmd_lst);
		else
		{
			printf("Commande recue = ");
			printf("%s \n", cmd_lst[0]);
			free(inpt);
			ft_free_the_tab(cmd_lst);
		}
	}
	return (0);
}
