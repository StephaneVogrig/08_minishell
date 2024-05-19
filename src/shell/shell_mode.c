/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:32:09 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/18 21:00:41 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_bool	shell_mode_init_interactive(t_env *env)
{
		(void)env;
	// if (!env_new("-", "i", 0, env))
	// 	return (FAILURE);
	return (SUCCESS);
}

t_bool	shell_mode_init_file(t_env *env)
{
		(void)env;
	// if (!env_new("-", NULL, 0, env))
	// 	return (FAILURE);
	return (SUCCESS);
}

t_bool	shell_is_interactive(t_env *env)
{
	char	*mode;

	mode = env_get(env, "-");
	return (mode != NULL);
}