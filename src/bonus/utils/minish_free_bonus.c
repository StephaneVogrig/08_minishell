/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_free_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:11:33 by stephane          #+#    #+#             */
/*   Updated: 2024/06/18 17:32:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish_free.h"
#include "pipelist_bonus.h"

void	minishell_free(t_cmd *cmd, char *str, char **argv, t_env *env)
{
	if (str)
		free(str);
	strtab_free(argv);
	env_free(env);
	pipelist_free(cmd);
}
