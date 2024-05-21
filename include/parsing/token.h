/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:16:27 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/21 19:25:50 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "next_token_dequoted.h"
# include "next_token_limiter.h"
# include "parse.h"
# include "redirection.h"

t_char_m	*next_token_to_heredoc(char *str, t_redir **redir);
t_char_m	*next_token_to_redir(char *input, t_redir **redir, t_env *env);
char		*next_token_to_strlist(char *str, t_list **tokenlist, t_env *env);

#endif