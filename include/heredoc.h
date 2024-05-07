/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:15:43 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/07 18:11:31 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "libft.h"
# include "environment.h"
# include "exit.h"
# include "command.h"
# include "pipeline.h"
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "signal_handler.h"

# define INTERRUPT 10

t_bool	heredoc(t_cmd_m *pipeline, t_env_m *env, int *exit_status);
t_bool	heredoc_redir_loop(t_redir *redir, t_env_m *env, int *exit_status);

#endif