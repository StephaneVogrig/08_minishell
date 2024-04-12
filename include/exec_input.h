/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:37:35 by stephane          #+#    #+#             */
/*   Updated: 2024/04/11 20:50:54 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INPUT_H
# define EXEC_INPUT_H

# include "libft.h"
# include "pipeline.h"
# include "str.h"
# include "input_to_pipeline.h"
# include "pipex_bonus.h"
# include "pipeline_wait.h"
# include "process.h"

# define SYNTAX_ERROR 2

void	exec_input(char *input, char **envp, int *exit_status);

#endif