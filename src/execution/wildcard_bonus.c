/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:42:06 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/06 04:19:11 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"

void	wc_free(t_wildcard *wc)
{
	t_list	*node;
	t_list	*temp;

	node =  wc->list;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	wc->list = NULL;
}


int	ft_strcmp_rev(const char *big, const char *little) //NEW
{
	int	i;
	int j;

	i = ft_strlen(big) - ft_strlen(little);
	j = 0;
	if ( i < 0)
		return (-1);
	while (little[j])
	{
		if (big[i] == '\0' || big[i] != little[j])
			return ((unsigned char)big[i] - (unsigned char)little[j]);
		i++;
		j++;
	}
	return (0);
}

char	*mini_strstr(const char *big, const char *little)
{
	int	i;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (*big)
	{
		if (*big == *little)
		{
			i = 0;
			while (big[i] == little[i] && big[i])
				i++;
			if (little[i] == '\0')
				return ((char *)big);
		}
		big++;
	}
	return (NULL);
}

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
// ft_printf("str: %20s  | node: %10s", str, node->content);
		str = mini_strstr(str, node->content);
// ft_printf(" | strptr: %p\n", str);
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
		// printf("%s\n", dir->d_name);
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

static t_bool	str_to_wc(char *str, t_wildcard *wc)
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

void	display_argv_lst(t_list *lst)
{
	if (lst == NULL)
	{
		ft_printf("argv is null \n");
		return ;
	}
	while (lst != NULL)
	{
		ft_printf("-> %s \n", lst->content);
		lst = lst->next;
	}
}
t_bool	wildcard_to_list(char *format, t_list **strlist)
{
	t_wildcard wc;

	wc.list = NULL;
	wc.flags = 0;
	if (str_to_wc(format, &wc) == FAILURE)
		return (FAILURE);
	display_argv_lst(wc.list);
	// printf("wildcard_to_list\n");
	if (wildcard_select(&wc, strlist) == FAILURE)
	{
		wc_free(&wc);
		return (FAILURE);
	}
	wc_free(&wc);
	// printf("test\n");
	return (SUCCESS);
}