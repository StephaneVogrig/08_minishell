/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:11:31 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:47:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISE_BONUS_H
# define TOKENISE_BONUS_H

# include <errno.h>
# include "tokenlist_bonus.h"
# include "syntax_error_utils_bonus.h"

t_tokenlist_m	*tokenise(char *str);

/* tokenise_parse.c ***********************************************************/

char			*tokenise_and(char *str, t_tokenlist **tokens);
char			*tokenise_pipe(char *str, t_tokenlist **tokens);
char			*tokenise_redir(char *str, t_tokenlist **tokens);
char			*tokenise_word(char *str, t_tokenlist **tokens);
char			*tokenise_add(char *str, t_tokenlist **tokens, int type);

#endif
