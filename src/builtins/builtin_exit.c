/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:20:41 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/21 14:52:21 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_bool	is_num(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
	{
		if (!ft_isdigit(str[1]))
			return (FALSE);
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t')//mod
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '\t' && str[i] != ' ')//mod
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	exit_val_2(t_cmd *cmd, t_env *env, char *argv, int last)
{
	if(last == 1)
		write(STDERR_FD, "exit\n", 5);
	fd_printf(STDERR_FD, "minishel : exit : %s", argv);
	fd_printf(STDERR_FD, " : numeric argument required\n");
	cmd_free(cmd);
	env_free(env);
	exit(2);
}

int	exit_val_num(t_cmd *cmd, t_env *env, char *argv, int last)
{
	long long	exit_val;

	exit_val = ft_atol(argv);
	if(exit_val < 0 && !ft_strchr(argv, '-'))
		exit_val_2(cmd, env, argv, last);
	if(exit_val > 0 && ft_strchr(argv, '-'))
		exit_val_2(cmd, env, argv, last);
	cmd_free(cmd);
	env_free(env);
	if(last == 1)
		write(STDERR_FD, "exit\n", 5);
	exit((int)exit_val);
}

int	exit_mini(t_cmd *cmd, t_env *env, t_list *argv, int last)
{
	
	if (!argv->next)
	{
		if (!is_num(argv->content))
			exit_val_2(cmd, env, argv->content, last);
		exit_val_num(cmd, env, argv->content, last);
	}
	if (argv->next)
	{
		if (!is_num(argv->content))
			exit_val_2(cmd, env, argv->content, last);
		else
		{
			if(ft_atol(argv->content) < 0 && !ft_strchr(argv->content, '-'))
				exit_val_2(cmd, env, argv->content, last);
			if(ft_atol(argv->content) > 0 && ft_strchr(argv->content, '-'))
				exit_val_2(cmd, env, argv->content, last);
			if(last == 1)
				write(STDERR_FD, "exit\n", 5);
			fd_printf(STDERR_FD, "minishell : exit : too many arguments\n");
		}
	}
	return (1);
}


int	builtin_exit(t_cmd *cmd, t_env *env)
{
	t_list *argv;
	int		exit_code;
	t_cmd 	*lst;
	int 	last;
	t_redir *redir;

	last = 1;
	redir = cmd->redir;
	argv = cmd->argv->next;
	lst = cmd->next;
	if (lst)
		last = 0;
	if (!argv && last == 1)
	{
		exit_code = exit_status_get_int(env);
		cmd_free(cmd);
		env_free(env);
		if(!redir)
			write(3, "exit\n", 5);
		if(redir)
			write(STDERR_FD, "exit\n", 5);
		exit(exit_code);
	}
	return (exit_mini(cmd, env, argv, last));
}
