/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 05:44:26 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/06 15:48:33 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv.h"

t_bool	argv_add_buffer(t_list **argv, t_buff *buffer)
{
	t_char_m	*token;

	token = buff_to_str(buffer);
	buff_clear(buffer);
	if(!token)
		return (FAILURE);
	return (add_to_strlist(argv, token));
}

// char	**argv_empty(void)
// {
// 	char	**argv;
// 	char	*empty_str;

// 	argv = NULL;
// 	empty_str = ft_calloc(1, 1);
// 	if (!empty_str)
// 	{
// 		perror("minishell: argv_empty: calloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	argv = malloc(sizeof(char *) * 2);
// 	if (!argv)
// 	{
// 		free(empty_str);
// 		perror("minishell: argv_empty: malloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	argv[0] = empty_str;
// 	argv[1] = NULL;
// 	return (argv);
// }