/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_free_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:11:33 by stephane          #+#    #+#             */
/*   Updated: 2024/06/13 23:37:28 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/


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
