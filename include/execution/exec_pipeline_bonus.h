/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:43:05 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/04 22:09:49 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_PIPELINE_BONUS_H
# define EXEC_PIPELINE_BONUS_H

# include "command.h"
# include "environment.h"
# include "process_bonus.h"
# include "pipeline_wait.h"
# include <unistd.h>

int	exec_pipeline(t_cmd_m *pipeline, t_env **env);

#endif