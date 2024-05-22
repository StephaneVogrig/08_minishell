/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:32:09 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/22 16:10:09 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_mode.h"

int event(void)
{
	return (0);
}

t_bool	shell_mode_init_interactive(t_env **env)
{
	if (env_add_new("-", "i", 0, env) == FAILURE)
		return (FAILURE);
	rl_event_hook = event;
	rl_outstream = stderr;
	return (SUCCESS);
}

t_bool	shell_mode_init_file(t_env **env)
{
	if (env_add_new("-", NULL, 0, env) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_bool	shell_is_interactive(t_env *env)
{
	char	*mode;

	mode = env_get(env, "-");
	return (mode != NULL);
}
