/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:26:47 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/31 16:04:37 by smortemo         ###   ########.fr       */
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
		return (ENOENT);
	ft_printf("%s\n", str);
	return (0);
}
