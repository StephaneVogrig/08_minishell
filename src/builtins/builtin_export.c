/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:13:40 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/18 18:07:41 by smortemo         ###   ########.fr       */
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

// les 2 fct suivantes sont dans manage_node.c (+declaration environment.h)
// t_bool	var_init(t_env *node, char *str, int n) 
// int	export_new_node(t_env *env, char *str, int n)

static int	export_run(t_env *env, char *str)
{
	int		n;
	t_env	*node;

	n = end_var_name(str);
	node = env_get_node_n(env, str, n);
	if (node && str[n] == '=')
	{
		free(node->value);
		node->type = EXPORTED;
		node->value = ft_strdup(&str[n + 1]);
	}
	if (node && str[n] == '+')
		node->value = ft_strjoin_free_s1(node->value, &str[n + 2]);
	if (!node)
		return (export_new_node(env, str, n));
	return (0);
}

int	export(t_env *envp, char *str)
{
	if (!is_valid_arg(str))
	{
		fd_printf(STDERR_FD, "minishel : export : '%s'", str);
		fd_printf(STDERR_FD, " : not a valid identifier\n");
		return (1);
	}
	return (export_run(envp, str));
}

int	builtin_export(t_cmd *cmd, t_env *env)
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
		return (display_envp_sorted(env));
	while (argv)
	{
		error = export(env, argv->content);
		if (error == ENOMEM)
		{
			env_free(env);
			pipeline_free(&cmd);
			exit(EXIT_FAILURE);
		}
		if (error == 1)
			ret = 1;
		argv = argv->next;
	}
	return (ret);
}
