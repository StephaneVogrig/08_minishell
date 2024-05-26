/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 00:11:51 by stephane          #+#    #+#             */
/*   Updated: 2024/05/27 01:39:37 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

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

t_bool	is_token_empty(char *str, t_env *env)
{
	char	*end;

	if (*str != '$')
		return (FALSE);
	while (*str && !is_meta(*str))
	{
		if (*str == '$')
		{
			end = end_name(++str);
			if (end == str)
				return (FALSE);
			if (env_get_n(env, str, end - str))
				return (FALSE);
			str = end;
		}
		else
			return (FALSE);
	}
	return (TRUE);
}

char	*next_token_to_strlist(char *str, t_list **strlist, t_env *env)
{
	t_buff	buffer;

	if (is_token_empty(str, env))
	{
		while (*str && !is_meta(*str))
			str++;
		return (str);
	}
	buff_init(&buffer);
	while (str && !is_meta(*str))
	{
		if (*str == '\'')
			str = parse_spl_quoted(&buffer, str);
		else if (*str == '\"')
			str = parse_dbl_quoted(&buffer, str, env);
		else if (*str == '$')
			str = expanse_unquoted(&buffer, ++str, strlist, env);
		else if (buff_add_char(&buffer, *str++) == FAILURE)
			str = NULL;
	}
	if (!str || strlist_add_buffer(strlist, &buffer) == FAILURE)
		str = NULL;
	buff_clear(&buffer);
	return (str);
}
