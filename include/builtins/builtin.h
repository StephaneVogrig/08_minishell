/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:55 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/19 17:36:29 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "command.h"
# include "environment.h"
# include "exec_cmd.h"
# include "libft.h"
# include <errno.h>

typedef int (*t_builtin)(t_cmd *, t_env *);

// UTILS ---------------------------------
int		display_envp_sorted(t_env *envp);
int 	(*builtin_function(t_list *argv))(t_cmd *, t_env *);
int		exec_builtin_alone(t_builtin builtin, t_cmd *cmd, t_env *env);

// BUILTINS ------------------------------

int		builtin_pwd(t_cmd *cmd, t_env *env);
int		builtin_env(t_cmd *cmd, t_env *env);
int		builtin_export(t_cmd *cmd, t_env *env);
int		builtin_unset(t_cmd *cmd, t_env *env);
int		builtin_echo(t_cmd *cmd, t_env *env);
int		builtin_cd(t_cmd *cmd, t_env *env);
int		builtin_exit(t_cmd *cmd, t_env *env);

#endif