/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:16:27 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/04 11:03:39 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "next_token_dequoted.h"
# include "next_token_limiter.h"
# include "next_token_to_str.h"
# include "expanse.h"
# include "redirection.h"

t_char_m	*next_token_to_heredoc(char *str, t_redir **redir);
t_char_m	*next_token_to_redir(char *input, t_redir **redir);
char		*next_token_to_arglist(char *input, t_list **arglist);

#endif