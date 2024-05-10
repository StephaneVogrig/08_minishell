/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:15:43 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/10 16:44:44 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef HEREDOC_H
# define HEREDOC_H

# include "libft.h"
# include "expanse.h"
# include "exit.h"
# include "command.h"
# include "pipeline.h"
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "signal_handler.h"
# include <wait.h>

# define INTERRUPT 10

t_bool	heredoc(t_cmd_m *pipeline, t_env_m *env, int *exit_status);
t_bool	heredoc_redir_loop(t_list **limlist, t_redir *redir, t_env *env, int *exit_status);

#endif