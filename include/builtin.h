/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:55 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/04 22:34:33 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "command.h"
# include "environment.h"
# include "exec_cmd.h"
# include "libft.h"
# include <errno.h>

// UTILS ---------------------------------
int		display_envp_sorted(t_env *envp);
t_bool	builtin_is_executed(t_cmd *cmd, t_env *env, int *exit_status);

// BUILTINS ------------------------------

int		builtin_pwd(t_cmd *cmd, t_env *env);
int		builtin_env(t_cmd *cmd, t_env *env);
int		builtin_export(t_cmd *cmd, t_env *env);
int		builtin_unset(t_cmd *cmd, t_env *env);
int		builtin_echo(t_cmd *cmd, t_env *env);
int		builtin_cd(t_cmd *cmd, t_env *env);
int		builtin_exit(t_cmd *cmd, t_env *env);

#endif