/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:25:18 by stephane          #+#    #+#             */
/*   Updated: 2024/05/07 00:34:05 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_to_pipeline.h"

t_bool	is_meta(char c)
{
	if (ft_strchr("|<> \t", c))
		return (TRUE);
	return (FALSE);
}

int	strlen_unquoted(char *str)
{
	char	*temp;
	char	quote;

	temp = str;
	while (!is_meta(*str))
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			while (*str != quote)
				str++;
			str++;
			continue;
		}
		str++;
	}
	return (str - temp);
}


t_bool	add_to_redir(t_list *strlist, int type, t_redir **redir, char *str)
{
	if (!strlist)
		return (FAILURE);
	if (strlist->next)
	{
		fd_printf(STDERR_FD, "minishell: %s: ambiguous redirect\n", str);
		ft_lstclear(&strlist, free);
		return (FAILURE);
	}
	if (!redirection_add(redir, strlist->content, type))
	{
		ft_lstclear(&strlist, free);
		return (FAILURE);
	}
	return (SUCCESS);
}

t_char_m	*next_token_to_redir(char *input, t_redir **redir, t_env *env, int *exit_status)
{
	t_list		*strlist;
	char		c;
	int			type;
	char	*str;

	str = input;
	strlist = NULL;
	c = *str++;
	if (c == '<')
			type = IN;
	else if (*str =='>')
	{
		type = OUT | APPEND;
		str++;
	}
	else
		type = OUT;
	str = skip_blank(str);
	str = add_next_token(str, &strlist, env, exit_status);
	if (add_to_redir(strlist, type, redir, input) == FAILURE)
		return (NULL);
	free(strlist);
// print_redir(*redir);
// ft_printf("len:%i, tok:\"%s\"\n", len, token);
	return (str);
}

t_bool	strfill_unquoted(char *dest, char *src)
{
	char		quote;

	quote = '\0';
	while (!is_meta(*src))
	{
		if (*src == '\'' || *src == '\"')
		{
			quote = *src++;
			while (*src != quote)
				*dest++ = *src++;
			src++;
			continue ;
		}
		*dest++ = *src++;
	}
	*dest = '\0';
	return (quote != '\0');
}

t_char_m	*next_token_to_heredoc(char *str, t_redir **redir)
{
	t_char_m	*token;
	int			len;
	int			type;
	t_bool		dequoted;

	str = skip_blank(str);
	len = strlen_unquoted(str);
	token = malloc(len + 1);
	if	(!token)
		return (NULL);
	dequoted = strfill_unquoted(token, str);
	if (dequoted)
		type = IN | HEREDOC;
	else
		type = IN | HEREDOC | EXPANSE;
	if (!redirection_add(redir, token, type))
		return (NULL);
	return (str + len);
}

char	*new_current_cmd(t_cmd **cmd, char *str)
{
	t_cmd	*new;	

	new = cmd_new();
	if (!new)
		return (NULL);
	new->previous = *cmd;
	(*cmd)->next = new;
	*cmd = new;
	return (++str);
}

char	*parse(char *input, t_cmd **cmd, t_env *env, int *exit_status)
{
	if (*input == '|')
		return (new_current_cmd(cmd, input));
	if (*input == '<' && *(input + 1) == '<')
		return (next_token_to_heredoc(input + 2, &(*cmd)->redir));
	if (*input == '>' | *input == '<')
		return (next_token_to_redir(input, &(*cmd)->redir, env, exit_status));
	return (add_next_token(input, &((*cmd)->argv), env, exit_status));
}

t_cmd	*input_to_pipeline(char *input, t_env *env, int *exit_status)
{
	t_cmd	*pipeline;
	t_cmd	*current_cmd;

	current_cmd = cmd_new();
	if (!current_cmd)
		return (NULL);
	pipeline = current_cmd;
	while (*input)
	{
		input = parse(input, &current_cmd, env, exit_status);
		if (!input)
		{
			pipeline_free(&pipeline);
			return (NULL);
		}
		input = skip_blank(input);
	}
	return (pipeline);
}
