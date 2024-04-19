/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:23:08 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/19 18:31:22 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


void	builtin_env(char **envp)
{
	// env sans arg return=0
	// env avec arg doit etre chemin acces
	// si existe pas->127,si acces refuse->126
	if (envp == NULL)
		return ;
	while (*envp)
	{
		if (ft_strchr(*envp, '='))
		{
			ft_putstr_fd(*envp, STDOUT_FD);
			write(STDOUT_FD, "\n", 1);
		}
		envp++;
	}
}
