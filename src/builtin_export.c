/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:13:40 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/01 17:58:37 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "environment.h"

// void	export_error(char *str)
// {
// 	ft_putstr_fd("export: '", 2);
// 	ft_putstr_fd(str, 2);
// 	ft_putstr_fd("' : not a valid identifier\n", 2);
// }

// int	export_check_str(char **envp, char *str)
// {
// 	int		ret;
// 	char	*lst;

// 	lst = "!#$%%?$*-.,/}{}[]@~:";
// 	ret = ft_strchr_i(str, '=');
// 	if (!ret) //+ error = 0
// 		return (-1);
// 	while (ret >= 0)
// 	{
// 		if (ft_strchr(lst, str[ret])) //+ error = 1
// 		{
// 			export_error(str);
// 			return (1);
// 		}
// 		if (str[ret] == '+' && str[ret - 1] == '+') //+ error = 1
// 		{
// 			export_error(str);
// 			return (1);
// 		}
// 		ret--;
// 	}
// 	return (-1);
// }

// int	export_modify_var(char *envp, char *str)
// {
// 	free(envp);
// 	envp = ft_strdup(str);
// 	return (1);
// }

// int	export_check_exist(char **envp, char *str)
// {
// 	int	i;
// 	int	index;
// 	int	len;

// 	i = 0;
// 	index = ft_strchr_i(str, '=');
// 	len = ft_strlen(envp[i]);
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], str, index) == 0 && envp[i][index] == '=')
// 			// ex:  TEST=aaa
// 			return (export_modify_var(envp[i], str));
// 		else if (ft_strncmp(envp[i], str, index - 1) == 0 && str[index
// 				- 1] == '+') // ex: TEST+=newvalue
// 		{
// 			envp[i] = ft_strjoin_free_s1(envp[i], &(*str) + index + 1);
// 			return (1);
// 		}
// 		else if (ft_strncmp(envp[i], str, len) == 0 && str[len] == '=')
// 			// ex : TEST=value (avec TEST qui existe deja)
// 			return (export_modify_var(envp[i], str));
// 		i++;
// 	}
// 	return (0);
// }

// char	**builtin_export(char **envp, char *str)
// {
// 	int		i;
// 	char	**tab_temp;
// 	int		flag;

// 	if (!envp)
// 		return (NULL);
// 	// if (!str)
// 	// {
// 	// 	tab_temp = env_dup(envp);
// 	// 	export_alone(tab_temp); //+code erreur = 0
// 	// 	strtab_free(tab_temp);
// 	// 	return (envp);
// 	// }
// 	if (str[0] == '\0')
// 	{
// 		export_error(str);
// 		return (envp); //+code erreur = 1
// 	}
// 	if (export_check_str(envp, str) >= 0)
// 		return (envp);
// 	flag = export_check_exist(envp, str);
// 	tab_temp = mem_calloc(ft_strtab_size(envp) + 2 - flag, sizeof(char **));
// 	i = -1;
// 	while (envp[++i])
// 		tab_temp[i] = envp[i];
// 	if (flag == 0)
// 		tab_temp[i] = ft_strdup(str);
// 	free(envp);
// 	return (tab_temp); //+code erreur = 0
// }
/////////////////

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

t_bool	var_init(t_env *node, char *str, int n)
{
	node->name = ft_strndup(str, n);
	if (!node->name)
		return (FAILURE);
	if (str[n] != '\0')
	{
		node->value = ft_strdup(&str[n + 1]);
		if (!node->value)
			return (FAILURE);
		node->type = EXPORTED;
	}
	else
	{
		node->value = malloc(1);
		if (!node->value)
			return (FAILURE);
		node->value[0] = '\0';
		node->type = INTERNAL;
	}
	node->next = NULL;
	return (SUCCESS);
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

int	export_new_node(t_env *env, char *str, int n)
{
	t_env	*node;

	node = malloc(sizeof(*node));
	if (!node)
	{
		env_free(env);
		return (0);
	}
	if (!var_init(node, str, n))
		return (0);
	lst_add_back(&env, node);
	return (1);
}

int	export_run(t_env *env, char *str)
{
	int		n;
	int		len;
	t_env	*node;

	n = end_var_name(str);
	node = env_get_node_n(env, str, n);
	if (node && str[n] == '=')
	{
		free(node->value);
		node->value = ft_strdup(&str[n + 1]);
	}
	if (node && str[n] == '+')
		node->value = ft_strjoin_free_s1(node->value, &str[n + 2]);
	if (!node)
		export_new_node(env, str, n);
	return (0);
}

int	builtin_export(t_env *envp, char *str)
{
	if (!envp)
		return (0);
	if (!str)
		return (display_envp_sorted(envp));
	if (!is_valid_arg(str))
		return (1);
	return (export_run(envp, str));
}
