/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:43:05 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:54:44 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_PIPELINE_BONUS_H
# define EXEC_PIPELINE_BONUS_H

# include "command.h"
# include "environment.h"
# include "process_bonus.h"
# include "pipeline_wait.h"

int	exec_pipeline(t_cmd_m *pipeline, t_env **env, t_cmd *tofree);

#endif
