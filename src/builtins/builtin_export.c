/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:13:40 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/19 16:34:33 by smortemo         ###   ########.fr       */
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
	if(ft_strchr(str, '=') == NULL)
		return(ft_strlen(str));
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

static int	export_run(t_env *env, char *str)
{
	int		n;
	t_env	*node;

	// printf("---->fonction export run\n");
	n = end_var_name(str);
	// printf("end_var_name n=%d\n", n);
	// printf("value = str[n]:%s\n", &str[n]);
	if(str[n] != '\0')
		node = env_get_node_n(env, str, n);
	else
		node = env_get_node(env, str);
	// printf("recherche node: %p\n", node);
	// if (node)
	// 	printf("node->value: %s\n", node->value);
	if (node && str[n] == '=')
	{
		// printf("cas 1\n");
		free(node->value);
		if(str[n + 1])
		{
			// printf("cas 1.a\n");
			// printf("node->type = EXPORTED\n");
			node->value = ft_strdup(&str[n + 1]);
			node->type = EXPORTED;
		}
			
		else
		{
			// printf("cas 1.b\n");
			// printf("node->type = EXPORTED_malloc 1 \n");
			node->value = malloc(1);
			node->value[0] = '\0';
			node->type = EXPORTED;
		}
	}
	if (node && str[n] == '+')
	{
		// printf("cas 2\n");
		node->value = ft_strjoin_free_s1(node->value, &str[n + 2]);
		if (!node->value)
			return (ENOMEM);
	}
	if (!node)
	{
		// printf("cas 3\n");
		return (export_new_node(env, str, n));
	}
	// printf("FIN\n");
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
	{
		ret = display_envp_sorted(env);
		if (ret == ENOMEM)
			exit_on_failure(cmd, NULL, NULL, env);
	}	
	while (argv)
	{
		error = export(env, argv->content);
		if (error == ENOMEM)
			exit_on_failure(cmd, NULL, NULL, env);
		if (error == 1)
			ret = 1;
		argv = argv->next;
	}
	return (ret);
}
