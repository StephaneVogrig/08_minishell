/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 19:14:20 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/01 22:11:28 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int (*builtin_function(char *str))(t_cmd *, t_env *)
{
	// ft_printf("str= %s\n", str);
	if (!ft_strcmp(str, "export"))
		return (&builtin_export);
	if (!ft_strcmp(str, "unset"))
		return (&builtin_unset);
	return (NULL);
	// if (ft_strcomp(str, "echo"))
}

t_bool	builtin_is_executed(t_cmd *cmd, t_env *env)
{
	int (*builtin)(t_cmd *, t_env *);

	// ft_printf("builtin executed\n");
	builtin = builtin_function(cmd->argv->content);
	// ft_printf("builtin= %p\n", builtin);
	if (!builtin)
		return (FALSE);
	builtin(cmd, env);
	return (TRUE);
}