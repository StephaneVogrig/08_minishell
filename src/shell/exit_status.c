/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:58:54 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/18 17:16:01 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit_status.h"

t_bool	exit_status_create(t_env *env)
{
	if (!env_new("?", "0", INTERNAL, env))
		return (FAILURE);
	return (SUCCESS);
}

t_bool	exit_status_set(int value, t_env *env)
{
	t_char_m *str;

	str = ft_atoi(value);
	if (!str)
	{
		perror("minishell: ft_atoi");
		return (FAILURE);
	}
	env_set_value("?", str, env);
	return (SUCCESS);
}

inline char	*exit_status_get_str(t_env *env)
{
	return (env_get(env, "?"));
}
