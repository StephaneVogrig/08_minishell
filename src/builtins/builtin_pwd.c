/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:26:47 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/17 16:24:35 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
		return (EXIT_FAILURE);
	ft_printf("%s\n", str);
	return (EXIT_SUCCESS);
}
