/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:15:43 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/02 18:14:16 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef HEREDOC_H
# define HEREDOC_H

# include "expanse.h"
# include "exit.h"
# include "pipeline.h"
# include "signal_handler.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

int		heredoc_scan(int fd, t_redir *redir);
t_bool	heredoc(t_cmd_m *pipeline);
t_bool	heredoc_expand(t_redir *redir, t_env *env);

#endif