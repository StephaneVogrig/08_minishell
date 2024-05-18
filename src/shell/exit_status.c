/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:58:54 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/18 21:05:38 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_bool	exit_status_init(t_env **env)
{
	if (!env_add_new("!", "0", INTERNAL, env))
		return (FAILURE);
	return (SUCCESS);
}

t_bool	exit_status_set(int value, t_env *env)
{

		(void)env;
		(void)value;
	// t_char_m *str;

	// str = ft_atoi(value);
	// if (!str)
	// {
	// 	perror("minishell: ft_atoi");
	// 	return (FAILURE);
	// }
	// env_set_value("?", str, env);
	return (SUCCESS);
}

inline char	*exit_status_get_str(t_env *env)
{
	return (env_get(env, "?"));
}
