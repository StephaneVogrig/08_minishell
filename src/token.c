/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 00:11:51 by stephane          #+#    #+#             */
/*   Updated: 2024/05/07 07:38:27 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*next_token_to_heredoc(char *input, t_redir **redir)
{
	char	*token;
	int		type;
	t_bool	dequoted;

	input = skip_blank(input);
	input = next_token_dequoted(input, &token, &dequoted);
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

int	redir_type(char *str)
{
	if (*str == '<')
		return (IN);
	if (*(str + 1) == '>')
		return (OUT | APPEND);
	return (OUT);
}

char	*next_token_to_redir(char *input, t_redir **redir, \
											t_env *env, int *exit_status)
{
	t_list	*strlist;
	int		type;
	char	*str;

	str = input;
	strlist = NULL;
	type = redir_type(str++);
	if (*str == '>')
		str++;
	str = skip_blank(str);
	str = next_token_to_srtlist(str, &strlist, env, exit_status);
	if (redir_add_strlist(strlist, type, redir, input) == FAILURE)
		return (NULL);
	free(strlist);
	return (str);
}

char	*next_token_to_srtlist(char *str, t_list **argv, \
										t_env *env, int *exit_status)
{
	t_buff	buffer;
	
	buff_init(&buffer);
	while (str && !is_meta(*str))
	{
		if (*str == '\'')
			str = parse_spl_quoted(&buffer, str);
		else if (*str == '\"')
			str = parse_dbl_quoted(&buffer, str, env, exit_status);
		else if (*str == '$' && *(str + 1) == '?')
			str = expanse_exit_status(&buffer, ++str, exit_status);
		else if (*str == '$')
			str = expanse_unquoted(&buffer, ++str, argv, env);
		else if (buff_add_char(&buffer, *str++) == FAILURE)
			str = NULL;
	}
	if (str && argv_add_buffer(argv, &buffer) == FAILURE)
			str = NULL;
	buff_clear(&buffer);
	return (str);
}
