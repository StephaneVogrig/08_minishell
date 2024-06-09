/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:11:31 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/09 19:15:45 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISE_H
# define TOKENISE_H

# include <errno.h>
# include "tokenlist.h"
# include "syntax_error.h"


t_tokenlist_m	*tokenise(char *str);
char			*token_add(char *str, t_tokenlist **tokens, int type);
char			*tokenise_word(char *str, t_tokenlist **tokens);
char			*tokenise_redir(char *str, t_tokenlist **tokens);
int				syntax_error_msg_token(t_tokenlist *token);

/* tokenise_parse.c ***********************************************************/
char			*tokenise_parse(char *str, t_tokenlist **tokens);

#endif
