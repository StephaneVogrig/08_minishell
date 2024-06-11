/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:28:18 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:55:17 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_EXIT_UTILS_H
# define BUILTIN_EXIT_UTILS_H

# include "command.h"
# include "environment.h"
# include "mini_strtol.h"

t_bool	is_in_pipe(t_cmd *cmd);
void	print_exit(t_cmd *cmd, t_env *env);
t_bool	convert_arg(t_list *argv, int *exit_code);

#endif
