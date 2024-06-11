/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:18:23 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:56:10 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include "command.h"
# include "next_token_dequoted.h"
# include "next_token_limiter.h"
# include "next_token_to_str.h"
# include "expanse.h"
# include "redirection.h"

char		*new_current_cmd(t_cmd **cmd, char *str);
t_char_m	*next_token_to_heredoc(char *str, t_redir **redir);
t_char_m	*next_token_to_redir(char *input, t_redir **redir);
char		*next_token_to_arglist(char *input, t_list **arglist);

#endif
