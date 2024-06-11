/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 01:46:44 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/11 02:36:54 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard_bonus.h"
#include "unit_test.h"

t_bool	str_to_wc(char *str, t_wildcard *wc)
{
	if (!str)
		return (SUCCESS);
	if (*str == '*')
		wc->flags |= WILDCARD_FIRST;
	while (*str)
	{
		if (*str == '*')
		{
			wc->flags |= WILDCARD_LAST;
			*str = '\0';
			str++;
		}
		else
		{
			str = add_substr(str, wc);
			if (!str)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}

t_bool	wildcard_format_to_list(char *format, t_list **strlist)
{
	t_wildcard wc;

	wc.list = NULL;
	wc.flags = 0;
	if (str_to_wc(format, &wc) == FAILURE)
		return (FAILURE);
	if (wildcard_select(&wc, strlist) == FAILURE)
	{
		wc_free(&wc);
		return (FAILURE);
	}
	wc_free(&wc);
	return (SUCCESS);
}

static void	test(char *format)
{
	t_list	*strlist;

	strlist = NULL;
	unit_test(increase_tests);
	printf(GREEN"test %2i ", unit_test(get_tests));
	printf("input: %s"RESET"\n", format);

	format = ft_strdup(format);

	wildcard_format_to_list(format, &strlist);
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