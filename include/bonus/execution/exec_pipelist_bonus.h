/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipelist_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 02:37:23 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/13 03:41:35 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_PIPELIST_BONUS_H
# define EXEC_PIPELIST_BONUS_H

# include "command.h"
# include "environment.h"
# include "exec_pipeline.h"
# include "pipelist_bonus.h"

int	exec_pipelist(t_cmd *pipelist, t_env **env, t_cmd *tofree);

#endif
