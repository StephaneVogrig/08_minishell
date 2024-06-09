/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 01:13:40 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/09 17:55:16 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENLIST_H
# define TOKENLIST_H

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

typedef struct s_tokenlist{
	char				*str;
	int					type;
	struct s_tokenlist	*next;
}	t_tokenlist;

typedef t_tokenlist t_tokenlist_m;

# define SYNTAX_ERROR 2

/* token type */
# define NEWLINE 0
# define WORD 1

# define REDIR 2
# define IN 4
# define HEREDOC 8
# define OUT 16
# define APPEND 32

# define PARENTHESIS_OPEN 64
# define PARENTHESIS_CLOSE 128

# define SEMI_COLON 256
# define AND 512
# define OR 1024
# define PIPE 2048

t_tokenlist 	*token_new(char *str, int type);
void			tokenlist_free(t_tokenlist *token);
t_bool			tokenlist_add(t_tokenlist **token, char *str, int type);
void			tokenlist_add_back(t_tokenlist **tokens, t_tokenlist *token);

#endif