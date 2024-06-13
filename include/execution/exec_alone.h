/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_alone.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 04:35:58 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/13 04:42:41 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_ALONE_H
# define EXEC_ALONE_H

# include "command.h"
# include "environment.h"
# include "pipeline_wait.h"
# include "exec_cmd.h"
# include "exit.h"
# include "builtin.h"
# include "argv_expand.h"

int	exec_alone(t_cmd *cmd, t_env **env, t_cmd_m *data);

#endif