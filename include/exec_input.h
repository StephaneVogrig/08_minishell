/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:37:35 by stephane          #+#    #+#             */
/*   Updated: 2024/05/07 04:41:51 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INPUT_H
# define EXEC_INPUT_H

# include "builtin.h"
# include "heredoc.h"
# include "input_to_pipeline.h"
# include "pipeline.h"
# include "pipeline_wait.h"
# include "process.h"
# include "str.h"
# include "syntax_error.h"

# define SYNTAX_ERROR 2

void	exec_input(char *input, t_env *envp, int *exit_status);

#endif