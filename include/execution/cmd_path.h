/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 04:48:37 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/21 16:41:50 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PATH_H
# define CMD_PATH_H

# include "redirection.h"
# include "str.h"
# include "environment.h"
# include "exit.h"
# include <sys/stat.h>

char	*cmd_path(t_cmd_m *cmd, t_env_m *envp);

#endif