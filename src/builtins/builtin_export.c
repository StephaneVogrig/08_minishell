/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:13:40 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/09 23:26:58 by svogrig          ###   ########.fr       */
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

static int	export_modify_node(char *str, t_env *node, int n)
{
	if (node && str[n] == '\0')
		return (0);
	else if (node && str[n] == '=')
	{
		free(node->value);
		if (str[n + 1])
		{
			node->value = ft_strdup(&str[n + 1]);
			if (!node->value)
				return (ENOMEM);
		}
		else
		{
			node->value = malloc(1);
			if (!node->value)
				return (ENOMEM);
			node->value[0] = '\0';
		}
		node->type = EXPORTED;
		return (0);
	}
	node->value = ft_strjoin_free_s1(node->value, &str[n + 2]);
	if (!node->value)
		return (ENOMEM);
	return (0);
}

int	export_run(t_env **envp, char *str)
{
	int		n;
	t_env	*node;

	if (!is_valid_arg(str))
	{
		fd_printf(STDERR_FD, "minishel : export : `%s'", str);
		fd_printf(STDERR_FD, " : not a valid identifier\n");
		return (1);
	}
	n = end_var_name(str);
	node = env_get_node_n(*envp, str, n);
	if (!node)
		return (export_new_node(envp, str, n));
	else
	{
		if ((node->type == DIR_ || node->type == DIR_NO_VAL) && str[n] == '\0')
		{
			node->type = EXPORTED;
			return (0);
		}
		return (export_modify_node(str, node, n));
	}
}

int	builtin_export(t_cmd *cmd, t_env **env)
{
	t_list	*argv;
	int		error;
	int		ret;

	ret = EXIT_SUCCESS;
	if (!env)
		return (0);
	argv = cmd->argv;
	argv = argv->next;
	if (!argv)
	{
		if (display_envp_sorted(*env) == FAILURE)
			exit_on_failure(cmd, NULL, NULL, *env);
	}
	while (argv)
	{
		error = export_run(env, argv->content);
		if (error == ENOMEM)
			exit_on_failure(cmd, NULL, NULL, *env);
		if (error == EXIT_FAILURE)
			ret = EXIT_FAILURE;
		argv = argv->next;
	}
	return (ret);
}
