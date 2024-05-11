/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 03:13:01 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/07 05:32:01 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include "command.h"

void	redirlist_unlink_heredoc(t_redir *redir);
void	cmdlist_unlink_heredoc(t_cmd *cmd);
void	pipeline_free(t_cmd **pipeline);
t_cmd	*pipeline_add_newcmd(t_cmd **pipeline);

#endif