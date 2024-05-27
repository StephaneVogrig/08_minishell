/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:13:40 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/27 02:47:25 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_bool	is_valid_arg(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			if (str[i] == '+' && str[i + 1] == '=')
				return (TRUE);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	end_var_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			return (i);
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

static int	export_run(t_env **env, char *str)
{
	int		n;
	t_env	*node;

	n = end_var_name(str);
	node = env_get_node_n(*env, str, n);
	if (node && str[n] == '=')
	{
		free(node->value);
		if(str[n + 1])
		{		
			node->type = EXPORTED;
			node->value = ft_strdup(&str[n + 1]);
		}
		else
		{
			node->value = malloc(1);
			node->value[0] = '\0';
			node->type = EXPORTED;
		}	
	}
	if (node && str[n] == '+')
	{
		node->value = ft_strjoin_free_s1(node->value, &str[n + 2]);
		if (!node->value)
			return (ENOMEM);
	}
	if (!node)
		return (export_new_node(env, str, n));
	return (0);
}

int	export(t_env **envp, char *str)
{
	if (!is_valid_arg(str))
	{
		fd_printf(STDERR_FD, "minishel : export : '%s'", str);
		fd_printf(STDERR_FD, " : not a valid identifier\n");
		return (1);
	}
	return (export_run(envp, str));
}

int	builtin_export(t_cmd *cmd, t_env **env)
{
	t_list	*argv;
	int		error;
	int		ret;

	ret = 0;
	if (!env)
		return (0);
	argv = cmd->argv;
	argv = argv->next;
	if (!argv)
	{
		ret = display_envp_sorted(*env);
		if (ret == ENOMEM)
			exit_on_failure(cmd, NULL, NULL, *env);
	}	
	while (argv)
	{
		error = export(env, argv->content);
		if (error == ENOMEM)
			exit_on_failure(cmd, NULL, NULL, *env);
		if (error == EXIT_FAILURE)
			ret = EXIT_FAILURE;
		argv = argv->next;
	}
	return (ret);
}
