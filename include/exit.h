/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:00:10 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/05 07:58:28 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "environment.h"

void	minishell_free(t_char_m *str, t_char_m **argv, t_env_m *env);
void	exit_on_cmd_not_found(char **argv, t_env *env);
void	exit_on_open_error(char *file_path, int fd);
void	exit_on_failure(char *str, char **argv, t_env *env);

#endif
