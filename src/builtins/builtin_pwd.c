/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:26:47 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/19 17:10:08 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "environment.h"
#include <limits.h>

int	builtin_pwd(t_cmd *cmd, t_env **env)
{
	char	*str;
	char	buffer[PATH_MAX];

	(void)env;
	(void)cmd;
	str = getcwd(buffer, PATH_MAX);
	if (!str)
	{
		perror("minishell: builtin_pwd: getcwd");
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", str);
	return (EXIT_SUCCESS);
}
