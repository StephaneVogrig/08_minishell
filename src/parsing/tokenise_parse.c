/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 00:00:20 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/09 00:16:17 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenise.h"

char	*tokenise_parse(char *str, t_tokenlist **tokens)
{
		if (*str == '|')
			return (token_add(str, tokens, PIPE));
		if (*str == '<' || *str == '>')
			return (tokenise_redir(str, tokens));
		return (tokenise_word(str, tokens));
}
