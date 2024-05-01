/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:37:35 by stephane          #+#    #+#             */
/*   Updated: 2024/05/01 21:26:49 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INPUT_H
# define EXEC_INPUT_H

# include "builtin.h"
# include "input_to_pipeline.h"
# include "pipeline.h"
# include "pipeline_wait.h"
# include "pipex_bonus.h"
# include "process.h"
# include "str.h"
# include "syntax_error.h"

# define SYNTAX_ERROR 2

void	exec_input(char *input, t_env *envp, int *exit_status);

#endif