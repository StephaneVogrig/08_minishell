/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:37:35 by stephane          #+#    #+#             */
/*   Updated: 2024/04/06 23:04:09 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_INPUT_H
# define EXEC_INPUT_H

#include "libft.h"
#include "command.h"
#include "str.h"
#include "input_to_pipeline.h"
#include "pipex_bonus.h"

void	exec_input(char *input, char **envp);

#endif