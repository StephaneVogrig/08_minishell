/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 01:13:25 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 15:00:02 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenlist_bonus.h"

t_bool	tokenlist_add(t_tokenlist **token, char *str, int type)
{
	t_tokenlist	*new;

	new = token_new(str, type);
	if (!new)
		return (FAILURE);
	tokenlist_add_back(token, new);
	return (SUCCESS);
}

void	tokenlist_add_back(t_tokenlist **tokens, t_tokenlist *token)
{
	t_tokenlist	*temp;

	if (!*tokens)
	{
		*tokens = token;
		return ;
	}
	temp = *tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = token;
}

void	tokenlist_free(t_tokenlist *token)
{
	t_tokenlist	*temp;

	while (token)
	{
		temp = token->next;
		free(token);
		token = temp;
	}
}

t_tokenlist	*token_new(char *str, int type)
{
	t_tokenlist	*new;

	new = malloc(sizeof(*new));
	if (!new)
	{
		perror("minishell: token_new");
		return (NULL);
	}
	new->str = str;
	new->type = type;
	new->next = NULL;
	return (new);
}
