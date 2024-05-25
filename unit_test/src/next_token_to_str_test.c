/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token_to_str_test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:24:19 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/24 18:02:00 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "next_token_to_str.h"
#include <stdio.h>

static void	test(char *input, char *expected_str, char *expected_offset )
{
	char	*result;
	t_bool	success;

	unit_test(increase_tests);

	result = next_token_to_str(&input);
	if (!result)
	{
		perror("next_token_to_str");
		return ;
	}
	printf("test %2i ", unit_test(get_tests));
	success = ft_strcmp(result, expected_str) == 0;
	if (success)
	{
		printf(GREEN"[ok]"RESET"\n");	
		unit_test(increase_success);
	}
	else
	{
		printf(RED"[ko] "RESET);
		printf("input: %s\n", input);
		printf("expected: "GREEN"%s"RESET", result:"RED"%s\n"RESET, expected_str, result);
	}	
	free(result);
}

int	main(void)
{
	test("", "", "");
	test("'     '", "'     '", "'     '");
	test("42 21", "42", " 21");
	test("    \t\n42 21", "42", " 21");
	test("    \t\n\"\"42 21", "\"\"42", " 21");
	test("    \t\n\"    \"42 21", "\"    \"42", " 21");
	test("$    \t\n\"    \"42 21", "$", "    \t\n\"    \"42 21");

	unit_test_print_result("strtol", 10);
}