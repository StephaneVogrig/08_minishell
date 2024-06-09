/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:37:46 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/09 18:34:08 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenise.h"

void	tokenlist_print(t_tokenlist *tokens)
{
	while (tokens)
	{
		ft_printf("type: ");

		if (tokens->type & WORD)
			ft_printf("%s", "WORD ");
		if (tokens->type & REDIR)
			ft_printf("%s", "REDIR ");
		if (tokens->type & IN)
			ft_printf("%s", "IN ");
		if (tokens->type & HEREDOC)
			ft_printf("%s", "HEREDOC ");
		if (tokens->type & OUT)
			ft_printf("%s", "OUT ");
		if (tokens->type & APPEND)
			ft_printf("%s", "APPEND ");
		if (tokens->type & PIPE)
			ft_printf("%s", "PIPE ");
		if (tokens->type & OR)
			ft_printf("%s", "OR ");
		if (tokens->type & AND)
			ft_printf("%s", "AND ");

		ft_printf("%4i - str: %s\n", tokens->type, tokens->str);

		tokens = tokens->next;
	}
}

void	test(char *input)
{
	char *str;
	t_tokenlist	*tokens;

	str = ft_strdup(input);
	if (!str)
	{
		perror("test");
		return ;
	}
	ft_printf("input: %s\n", str);
	tokens = tokenise(str);
	ft_printf("input: %s\n", str);
	if (tokens)
		tokenlist_print(tokens);
	tokenlist_free(tokens);
	ft_printf("-------------------------------------\n");
	free(str);
}

int	main(void)
{
	ft_printf("-------------------------------------\n");
	test("''"); 
	test("\"\""); 
	test("\""); 
	test("'"); 
	test("<essai cat|cat >out"); 
	test("cat >out'sdf'");
	test(">"); 
	test("<"); 
	test("><"); 
	test("<>"); 
	test(">><<");
	test("<<>>");
	test("<>>");
	test(">>>");
	test("><<");
	test("<<<");
	test(">>>>");
	test("<<<<");
	test(">|"); 
	test("<|");
	test(">||"); 
	test("<||"); 
	test(">&"); 
	test("<&"); 
	test(">&&"); 
	test("<&&"); 
	test(">>|"); 
	test("<<|");
	test(">>||"); 
	test("<<||"); 
	test(">>&"); 
	test("<<&"); 
	test(">>&&"); 
	test("<<&&");
	test("<<               &&");
	test("<<         \t\t      &&");
	test("|| &&"); 
	test("|||"); 
	test("&&&"); 
	test("'|''||''&''&&'"); 
	test("||||||||||||||||||||||||"); 
	return (0);
}
