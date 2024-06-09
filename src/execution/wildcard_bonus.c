/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:42:06 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/09 22:32:48 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"

t_bool	wildcard_match(char *str, t_wildcard *wc)
{
	t_list	*node;
	node = wc->list;
	if (!node)
		return (TRUE);
	if (!(wc->flags & WILDCARD_FIRST))
	{
		if (ft_strncmp(str, node->content, ft_strlen(node->content)) != 0)
			return (FALSE);
	}
	while (node)
	{
		str = mini_strstr(str, node->content);
		if (!str)
			return (FALSE);
		node = node->next;
	}
	if (!(wc->flags & WILDCARD_LAST))
	{
		if (ft_strcmp_rev(str, (ft_lstlast(wc->list))->content) != 0)
			return (FALSE);
	}
	return (TRUE);
}

t_bool	wildcard_select(t_wildcard *wc, t_list **lst)
{
	DIR				*directory;
	struct dirent	*dirent;

	directory = opendir(".");
	if (!directory)
	{
		perror("minishell: wildcard_select: opendir");
		return (FAILURE);
	}
	dirent = readdir(directory);
	while (dirent != NULL)
	{
		if (wildcard_match(dirent->d_name, wc) == TRUE)
			if (ft_lstadd_back_new(lst, dirent->d_name) == FAILURE)
				return (FAILURE);
		dirent = readdir(directory);
	}
	closedir(directory);
	return (SUCCESS);
}

static char	*add_substr(char *str, t_wildcard *wc)
{
	char	quote;
	
	if (ft_lstadd_back_new(&wc->list, str) == FAILURE)
	{
		perror("minishell: str_to_wc: ft_lstadd_back_new");
		wc_free(wc);
		return (NULL);
	}
	wc->flags &= ~WILDCARD_LAST;
	while (*str && *str != '*')
	{
		if (*str == '\"' || *str == '\'')
		{
			quote = *str;
			str++;
			while (*str && *str != quote)
				str++;
			if (*str == '\0')
				break;
		}
		str++;
	}
	return (str);	
}

t_bool	str_to_wc(char *str, t_wildcard *wc)
{
	char	*temp;

	if (!str)
		return (SUCCESS);
	if (*str == '*')
		wc->flags |= WILDCARD_FIRST;
	while (*str)
	{
		if (*str == '*')
		{
			wc->flags |= WILDCARD_LAST;
			*str = '\0';
			str++;
		}
		else
		{
			str = add_substr(str, wc);
			if (!str)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}

t_bool	wildcard_format_to_list(char *format, t_list **strlist)
{
	t_wildcard wc;

	wc.list = NULL;
	wc.flags = 0;
	if (str_to_wc(format, &wc) == FAILURE)
		return (FAILURE);
	if (wildcard_select(&wc, strlist) == FAILURE)
	{
		wc_free(&wc);
		return (FAILURE);
	}
	wc_free(&wc);
	return (SUCCESS);
}