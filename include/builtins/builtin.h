/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:55 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/01 13:36:40 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "builtin_exit_utils.h"
# include "exec_cmd.h"
# include "exec_redir.h"
# include "libft.h"
# include <errno.h>

typedef int	(*t_builtin)(t_cmd *, t_env **);

// UTILS ---------------------------------
t_bool		display_envp_sorted(t_env *envp);
t_builtin	builtin_function(t_list *argv);
int			exec_builtin_alone(t_builtin builtin, t_cmd *cmd, t_env **env);

// BUILTINS ------------------------------
int			builtin_pwd(t_cmd *cmd, t_env **env);
int			builtin_env(t_cmd *cmd, t_env **env);
int			builtin_export(t_cmd *cmd, t_env **env);
int			builtin_unset(t_cmd *cmd, t_env **env);
int			builtin_echo(t_cmd *cmd, t_env **env);
int			builtin_cd(t_cmd *cmd, t_env **env);
int			builtin_exit(t_cmd *cmd, t_env **env);

#endif