/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:00:10 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/13 04:01:43 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include <string.h>
# include <errno.h>
# include "minishell_free.h"

# define NO_SUCH_FILE 0
# define CMD_NOT_FOUND 1

void	exit_on_file_error(char *msg, t_cmd *cmd, t_env *env, t_cmd *data);
void	exit_on_open_error(char *file_path, int fd);
void	exit_on_failure(t_cmd *cmd, char *str, char **argv, t_env *env);

#endif
