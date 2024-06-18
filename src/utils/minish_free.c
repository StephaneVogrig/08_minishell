/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:02:54 by stephane          #+#    #+#             */
/*   Updated: 2024/06/18 17:37:12 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish_free.h"
#include "pipeline.h"

void	minishell_free(t_cmd *cmd, char *str, char **argv, t_env *env)
{
	if (str)
		free(str);
	strtab_free(argv);
	env_free(env);
	pipeline_free(&cmd);
}
