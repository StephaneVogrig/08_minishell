/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:25:18 by stephane          #+#    #+#             */
/*   Updated: 2024/04/25 20:26:07 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "input_to_pipeline.h"

t_bool	is_meta(char c)
{

	if (ft_strchr("|<> \t", c))
		return (TRUE);
	return (FALSE);
	
}

int	token_len(char *str)
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
		}
		str++;
	}
	return (str - temp);
}

t_char_m	*next_token_to_redir(char *str, t_redir **redir, int type)
{
	t_char_m	*token;
	int			len;

	str = skip_blank(str);
	len = token_len(str);
	token = ft_strndup(str, len);
	if	(!token && !redirection_add(redir, token, type))
		return (NULL);
ft_printf("len:%i, tok:\"%s\"\n", len, token);
	return (str + len);
}

char	*new_current_cmd(t_cmd **cmd, char *str)
{
	(*cmd)->next = cmd_new();
	if (!(*cmd)->next)
		return (NULL);
	*cmd = (*cmd)->next;
	return (++str);
}

char	*parse(char *input, t_cmd **cmd)
{
	if (*input == '|')
		return (new_current_cmd(cmd, input));
	if (*input == '<' && *(input + 1) == '<')
		return (next_token_to_redir(input + 2, &(*cmd)->redir, HEREDOC));
	if (*input == '<')
		return (next_token_to_redir(input + 1, &(*cmd)->redir, REDIR_IN));
	if (*input == '>' && *(input + 1) == '>')
		return (next_token_to_redir(input + 2, &(*cmd)->redir, REDIR_OUT_APD));
	if (*input == '>')
		return (next_token_to_redir(input + 1, &(*cmd)->redir, REDIR_OUT_TRC));
	return (add_next_token(input, &((*cmd)->argv)));
}

t_cmd	*input_to_pipeline(char *input)
{
	t_cmd	*pipeline;
	t_cmd	*current_cmd;
	
	current_cmd = cmd_new();
	if (!current_cmd)
		return (NULL);
	pipeline = current_cmd;
	while (*input)
	{
		input = parse(input, &current_cmd);
		if (!input)
		{
			pipeline_free(&pipeline);
			return (NULL);
		}
		input = skip_blank(input);
	}
	return (pipeline);
}
