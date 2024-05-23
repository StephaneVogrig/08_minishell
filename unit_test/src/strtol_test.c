/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtol_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:15:57 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/23 13:40:30 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <stdio.h>

static void	test(char *str, long expected_nbr, char *expected_endptr)
{
	char	*endptr;
	long	nbr;
	t_bool	success;
	char	*color;

	unit_test(increase_tests);

	nbr = mini_strtol(str, &endptr);

	printf("test %2i ", unit_test(get_tests));
	if ((expected_nbr == nbr) && (ft_strcmp(endptr, expected_endptr) == 0))
	{
		printf(GREEN"[ok]\n"RESET);	
		unit_test(increase_success);
	}
	else
	{
		printf(RED"[ko]\n"RESET);
		printf("input: %s\n", str);
		if (expected_nbr != nbr)
			printf("return : "GREEN"%li"RESET", "RED"%li\n"RESET, expected_nbr, nbr);
		if (ft_strcmp(endptr, expected_endptr) != 0)
			printf("endptr : "GREEN"%s"RESET", "RED"%s\n"RESET, expected_endptr, endptr);
	}	
}

int	main(void)
{
	test("", 0, "\0");
	test("42", 42, "\0");
	test("+42", 42, "\0");
	test("-42", -42, "\0");
	test("9223372036854775807", LONG_MAX, "\0");
	test("+9223372036854775807", LONG_MAX, "\0");
	test("-9223372036854775808", LONG_MIN, "\0");
	test("9223372036854775808", LONG_MAX, "8");
	test("+9223372036854775808", LONG_MAX, "8");
	test("-9223372036854775809", LONG_MIN, "9");
	test("-9223372036854775807", LONG_MIN + 1, "\0");
	test("92233720368547758070", LONG_MAX, "0");
	test("+92233720368547758070", LONG_MAX, "0");
	test("-92233720368547758080", LONG_MIN, "0");
	test("10000000000000000000", LONG_MAX, "0");
	test("-10000000000000000000", LONG_MIN, "0");
	test("0000000000000000000000000042", 42, "\0");
	test("-0000000000000000000000000042", -42, "\0");
	test("a42", 0, "a42");
	test("-a42", 0, "-a42");
	test("0a42", 0, "a42");
	test("-0a42", 0, "a42");
	test("  \t\t \n\n", 0, "\0");
	test("  \t\t \n\n42", 42, "\0");
	test("  \t\t \n\n-42", -42, "\0");
	test("  \t\t \n\n9223372036854775807", LONG_MAX, "\0");
	test("  \t\t \n\n-9223372036854775808", LONG_MIN, "\0");
	test("  \t\t \n\n000000000009223372036854775807", LONG_MAX, "\0");
	test("  \t\t \n\n-000000000009223372036854775808", LONG_MIN, "\0");
	test("  \t\t \n\n9223372036854775808", LONG_MAX, "8");
	test("  \t\t \n\n-9223372036854775809", LONG_MIN, "9");
	test("  \t\t \n\n-9223372036854775807", LONG_MIN + 1, "\0");
	test("  \t\t \n\n0000000000000000000000000042", 42, "\0");
	test("  \t\t \n\n-0000000000000000000000000042", -42, "\0");
	test("  \t\t \n\na42", 0, "a42");
	test("  \t\t \n\n-a42", 0, "-a42");
	test("  \t\t \n\n0a42", 0, "a42");
	test("  \t\t \n\n-0a42", 0, "a42");
	test("-", 0, "-");
	test("+", 0, "+");
	test("++", 0, "++");
	test("+-", 0, "+-");
	test("--", 0, "--");
	test("-+", 0, "-+");
	test("+0", 0, "\0");
	test("-0", 0, "\0");
	test("+0+", 0, "+");
	test("-0-", 0, "-");
	test("+0-", 0, "-");
	test("-0+", 0, "+");
	test("  \t\t \n\n00000000000000000000000000a42", 0, "a42");
	test("  \t\t \n\n-00000000000000000000000000a42", 0, "a42");
	test("+0000-42", 0, "-42");
	test("-0000+42", 0, "+42");
	test("0000-42", 0, "-42");
	test("0000+42", 0, "+42");
	unit_test_print_result("strtol", 10);
}