/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:38:28 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/17 20:56:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_H
# define EXEC_CMD_H

# include "libft.h"
# include "cmd_path.h"
# include "token.h"
# include "pipeline.h"
# include "redirection.h"
# include "signal.h"

t_bool	exec_redir(t_redir *redirs);
void	exec_cmd(t_cmd *cmd, t_env *env);

#endif