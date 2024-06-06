/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 01:46:44 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/06 04:07:30 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"
#include "unit_test.h"

static void	test(char *format)
{
	t_list	*strlist;

	strlist = NULL;
	unit_test(increase_tests);
	printf(GREEN"test %2i ", unit_test(get_tests));
	printf("input: %s"RESET"\n", format);

	format = ft_strdup(format);

	wildcard_to_list(format, &strlist);
	// printf("strlist= %p\n", strlist);

	strlist_print_fd(strlist, 2);

	printf("-------------------------\n");
	
}

int	main(void)
{
	test("*");
	test("*n");
	test("*n*");
	test("n*");

	test("*n*s");
	test("*n*s*");
	test("n*s");
	test("n*s*");

	test("***");
	test("***n");
	test("***n***");
	test("n***");

	test("***n***s**");
	test("***n***s***");
	test("n***s");
	test("n****s***");

	test("*n*e*s");
	test("*n*e*s*");
	test("n*e*s");
	test("n*e*s*");

	test("*'*'*");

}