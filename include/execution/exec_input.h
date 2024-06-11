/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:37:35 by stephane          #+#    #+#             */
/*   Updated: 2024/06/11 14:55:43 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INPUT_H
# define EXEC_INPUT_H

# include "builtin.h"
# include "heredoc.h"
# include "pipeline_wait.h"
# include "str.h"
# include "syntax_error.h"
# include "exec_redir.h"

# include "exec_pipeline.h"
# include "input_to_pipeline.h"

# define SYNTAX_ERROR 2

int	exec_input(char *input, t_env **envp);

#endif
