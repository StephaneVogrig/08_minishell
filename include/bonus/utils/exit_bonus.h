/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:36:19 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:52:34 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_BONUS_H
# define EXIT_BONUS_H

# include "environment.h"
# include "pipelist_bonus.h"

void	exit_on_file_error_bonus(const char *msg, t_cmd *cmd, t_env *env, \
																t_cmd *tofree);
void	exit_on_failure_bonus(t_cmd *pipelist, t_env *env);

#endif
