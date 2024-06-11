/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:16:42 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 12:57:12 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

char	*new_current_cmd(t_cmd **cmd, char *str)
{
	t_cmd	*new;	

	new = cmd_new();
	if (!new)
		return (NULL);
	new->previous = *cmd;
	new->flag = PIPE;
	(*cmd)->next = new;
	*cmd = new;
	return (++str);
}

char	*next_token_to_heredoc(char *input, t_redir **redir)
{
	char	*token;
	int		type;
	t_bool	dequoted;

	input = skip_blank(input);
	input = next_token_to_limiter(input, &token, &dequoted);
	if (!token)
		return (NULL);
	if (dequoted)
		type = IN | HEREDOC;
	else
		type = IN | HEREDOC | EXPANSE;
	if (!redir_add_str(redir, token, type))
		return (NULL);
	return (input);
}

char	*redir_type(char *str, int *type)
{
	if (*str++ == '<')
	{
		*type = IN;
		return (str);
	}
	if (*str == '>')
	{
		*type = OUT | APPEND;
		return (++str);
	}
	*type = OUT;
	return (str);
}

char	*next_token_to_redir(char *input, t_redir **redir)
{
	int		type;
	char	*str;

	input = redir_type(input, &type);
	str = next_token_to_str(&input);
	if (!str)
		return (NULL);
	if (redir_add_str(redir, str, type) == FAILURE)
	{
		free(str);
		return (NULL);
	}
	return (input);
}

char	*next_token_to_arglist(char *input, t_list **arglist)
{
	char	*str;

	str = next_token_to_str(&input);
	if (!str)
		return (NULL);
	if (ft_lstadd_back_new(arglist, str) == FAILURE)
	{
		free(str);
		return (NULL);
	}
	return (input);
}
