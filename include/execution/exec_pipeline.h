/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:48:23 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/04 13:54:03 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_PIPELINE_H
# define EXEC_PIPELINE_H

# include "command.h"
# include "environment.h"
# include "process.h"
# include "pipeline_wait.h"

int	exec_pipeline(t_cmd_m *pipeline, t_env **env);

#endif