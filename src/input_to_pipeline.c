/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:25:18 by stephane          #+#    #+#             */
/*   Updated: 2024/04/12 17:37:52 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_to_pipeline.h"

char *next_token_to_redir_hd(char *str, t_redir **redir)
{
	char *token;
	int flags;

	str = skip_blank(str);
	str = next_token(str, &token);
	if (!str)
		return (NULL);
	if (ft_strchr(str, '\"') || ft_strchr(str, '\''))
		flags = HEREDOC_NO_EXPAND;
	else
		flags = HEREDOC_EXPAND;
	if (!redirection_add(redir, token, flags))
		return (NULL);
	return (str);
}

static t_bool syntax_error(char *str, int *error)
{
	char *char_error;

	if (*str == '\0')
	{
		fd_printf(STDERR_FD, "%snewline\'\n", SYNTAX_ERROR_MSG);
		*error = SYNTAX_ERROR;
		return (TRUE);
	}
	char_error = ft_strchr("|<>", *str);
	if (char_error)
	{
		fd_printf(STDERR_FD, "%s%c\'\n", SYNTAX_ERROR_MSG, *char_error);
		*error = SYNTAX_ERROR;
		return (TRUE);
	}
	return (FALSE);
}

char	*next_token2(char *str, int *error)
{
	int		size;
	char	quote;

	size = 0;
	while (*str && !is_blank(*str) && !is_operator(*str))
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			while (*str && *str++ != quote);
			if (!*str)
			{
				fd_printf(STDERR_FD, "%snewline\'\n", SYNTAX_ERROR_MSG);
				*error = SYNTAX_ERROR;
				break;
			}
		}
		str++;
	}
	return (str);
}

char *redir_add_token(char *str, t_redir **redir, int flags, int *error)
{
	*str++ = '\0';
	if (flags & R_OUT && *str == '>')
		flags |= R_APPEND;
	if (flags & R_IN && *str == '<')
		flags |= R_HEREDOC;
	while (is_blank(*str))
		*str++ = '\0';
	if (syntax_error(str, error))
		return (str);
	if (!redirection_add(redir, str, flags))
		return (NULL);
	str = next_token2(str, error);
	if (!str)
		return (NULL);
	return (str);
}

char *new_current_cmd(t_cmd **cmd, char *str)
{
	*str++ = '\0';
	(*cmd)->next = cmd_new();
	if (!(*cmd)->next)
		return (NULL);
	*cmd = (*cmd)->next;
	return (str);
}

char *next_token_to_redir_expanse(char *str, t_redir **redir, int flags)
{
	(void)redir;
	(void)flags;
	// t_buff buf;
	// char *temp;

	// buff_init(&buf);
	// str = skip_blank(str);
	// while (*str && !is_blank(*str) && !is_operator(*str))
	// {
	// 	if (*str == '$')
	// 		;
	// 	if (*str == '\'')
	// 	{
	// 		temp = strchr(str, '\'');

	// 		while (*str && *str != '\'')
	// 		{
	// 			if (!buff_add_char(&buf, *str))
	// 				break;
	// 			str++;
	// 		}
	// 	}
	// 	if (*str == '\"')
	// 		;
	// 	str++;
	// }
	// buff_clear(&buf);
	return (str);
}

char *parse(char *input, t_cmd **cmd, int *error)
{
	t_redir **redir;

	redir = &(*cmd)->redir;
	if (*input == '|')
		return (new_current_cmd(cmd, input));
	if (*input == '<')
		return (redir_add_token(input, redir, R_IN, error));
	if (*input == '>')
		return (redir_add_token(input, redir, R_OUT, error));
	return (add_next_token(input, &((*cmd)->argv)));
}

t_cmd *input_to_pipeline(char *input, int *error)
{
	t_cmd *pipeline;
	t_cmd *current_cmd;

	current_cmd = cmd_new();
	if (!current_cmd)
		return (NULL);
	pipeline = current_cmd;
	while (*input)
	{
		input = parse(input, &current_cmd, error);
		if (!input)
		{
			pipeline_free(&pipeline);
			return (NULL);
		}
		if (error)
			break ;
		while (is_blank(*input))
			*input++ = '\0';
	}
	return (pipeline);
}
