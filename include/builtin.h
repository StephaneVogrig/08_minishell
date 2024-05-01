/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:55 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/01 17:52:09 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "environment.h"
# include "libft.h"

void	export_alone(char **envp);
int		builtin_export(t_env *envp, char *str);
int		builtin_env(char **envp);
int		builtin_unset(t_env *env, char *str);
int		display_envp_sorted(t_env *envp);

#endif