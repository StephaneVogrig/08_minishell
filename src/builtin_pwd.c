/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:26:47 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/02 00:43:49 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "environment.h"

int	builtin_pwd(t_cmd *cmd, t_env *env)
{
	char *str;

	(void)cmd;
	str = env_get(env, "PWD_cpy");
	if (!str)
		return (ENOENT); // voir pour valeur erreur -> Stephane?
	ft_printf("%s\n", str);
	return (0);
}