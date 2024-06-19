/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:32:09 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/19 19:36:44 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_mode.h"

t_bool	shell_mode_init_interactive(t_env **env)
{
	if (env_add_new("-", "i", 0, env) == FAILURE)
		return (FAILURE);
	rl_outstream = stderr;
	return (SUCCESS);
}

t_bool	shell_mode_init_file(t_env **env)
{
	if (env_add_new("-", "", 0, env) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_bool	shell_mode_is_interactive(t_env *env)
{
	char	*mode;

	mode = env_get(env, "-");
	if (mode)
		return (*mode == 'i');
	return (FALSE);
}
