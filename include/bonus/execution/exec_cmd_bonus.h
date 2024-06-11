/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:38:28 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:54:40 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_CMD_BONUS_H
# define EXEC_CMD_BONUS_H

# include "libft.h"
# include "cmd_path.h"
# include "argv.h"
# include "pipeline.h"
# include "redirection.h"
# include "signal.h"
# include <sys/stat.h>

# include "exit_bonus.h"

void	exec_cmd(t_cmd *cmd, t_env **env, t_cmd *tofree);

#endif
