/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:42:06 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/11 02:43:37 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"

t_bool	wildcard_match(char *str, t_wildcard *wc)
{
	t_list	*node;
	int	len;

	node = wc->list;
	if (!node)
		return (TRUE);
	if (!(wc->flags & WILDCARD_FIRST))
	{
		len = ft_strlen(node->content);
		if (ft_strncmp(str, node->content, len) != 0)
			return (FALSE);
		str += len;
		node = node->next;
	}
	while (node)
	{
		str = mini_strstr(str, node->content);
		if (!str)
			return (FALSE);
		node = node->next;
	}
	if (!(wc->flags & WILDCARD_LAST))
		if (ft_strcmp_rev(str, (ft_lstlast(wc->list))->content) != 0)
			return (FALSE);
	return (TRUE);
}

t_bool	check_path(char *str, t_wildcard *wc, t_list **lst)
{
	char	*temp;

	if (wc->flags & WILDCARD_FIRST && *str == '.')
		return (SUCCESS);
	if (wildcard_match(str, wc) == TRUE)
	{
		temp = ft_strdup(str);
		if (!temp)
		{
			perror("minishell: check_path: ft_strdup");
			return (FAILURE);
		}
		if (ft_lstadd_back_new(lst, temp) == FAILURE)
		{
			perror("minishell: ft_lstadd_back_new: ft_strdup");
			free(temp);
			ft_lstclear(lst, free);
			return (FAILURE);
		}
	}
	return (SUCCESS);
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
		if (check_path(dirent->d_name, wc, lst) == FAILURE)
			return (FAILURE);
		dirent = readdir(directory);
	}
	closedir(directory);
	return (SUCCESS);
}

char	*add_substr(char *str, t_wildcard *wc)
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
