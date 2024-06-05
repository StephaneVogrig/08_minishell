/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:31:21 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/04 20:48:43 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INPUT_BONUS_H
# define EXEC_INPUT_BONUS_H

# include "builtin.h"
# include "heredoc.h"
# include "input_to_pipelist.h"
# include "pipeline_wait.h"
# include "str.h"
# include "syntax_error.h"
# include "exec_redir.h"
# include "exec_pipeline.h"
# include "environment.h"
# include "pipelist_bonus.h"

# define SYNTAX_ERROR 2

int	exec_input(char *input, t_env **envp);

#endif