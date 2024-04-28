/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 00:11:51 by stephane          #+#    #+#             */
/*   Updated: 2024/04/27 20:25:20 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "token.h"

char	*str_to_token(char *str, char *token)
{
	char	quote;

	while (*str && !is_blank(*str) && !is_operator(*str))
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			while (*str && *str != quote)
				*token++ = *str++;
			if (*str)
				str++;
			continue ;
		}
		*token++ = *str++;
	}
	*token = '\0';
	return (str);
}

int	len_next_token(char *str)
{
	int		size;
	char	quote;

	size = 0;
	while (*str && !is_blank(*str) && !is_operator(*str))
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *str++;
			while (*str && *str++ != quote)
				size++;
			if (*str)
				str++;
			continue ;
		}
		str++;
		size++;
	}
	return (size);
}

char	*next_token(char *str, char	**token)
{
	*token = malloc(len_next_token(str) + 1);
	if (!*token)
	{
		perror("minishell: next_token");
		return (NULL);
	}
	str = str_to_token(str, *token);
	return (str);
}

// char	*add_next_token(char *str, t_list **tokenlist)
// {
// 	char	*token;

// 	str = next_token(str, &token);
// 	if(!str)
// 		return (NULL);
// 	if (!add_to_strlist(tokenlist, token))
// 		return (NULL);
// 	return (str);
// }

t_bool	argv_add_buffer(t_list **argv, t_buff *buffer)
{
	t_char_m	*token;
	if (!buff_len(buffer))
		return (SUCCESS);
	token = buff_to_str(buffer);
	buff_clear(buffer);
	if(!token)
		return (FAILURE);
	return (add_to_strlist(argv, token));
}

char	*add_next_token(char *str, t_list **argv, char **env, int *exit_status)
{
	t_buff	buffer;
	
	buff_init(&buffer);
	while (str && *str && ft_strchr("|<> \t", *str) == NULL)
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
