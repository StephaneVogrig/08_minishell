/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 03:43:02 by svogrig           #+#    #+#             */
/*   Updated: 2024/03/31 06:17:21 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define true 1
#define false 0

int glob_match(char const *pat, char const *str)
{
	char const *back_pat;
	char const *back_str;
	unsigned char c_str;
	unsigned char c_pat;
 
	back_pat = NULL;
	while (1) 
	{
		c_str = *str++;
		c_pat = *pat++;

		if (c_pat == '*')
		{
			if (*pat == '\0')	/* Optimize trailing * case */
				return true;
			back_pat = pat;
			back_str = --str;	/* Allow zero-length match */
		}
		else
		{
			if (c_str == c_pat)
			{
				if (c_pat == '\0')
					return true;
				continue;
			}
			if (c_str == '\0' || !back_pat)
				return false;	/* No point continuing */
			pat = back_pat;/* Try again from last *, one character later in str. */
			str = ++back_str;
		}
	}
}

int glob_match2(char const *pat, char const *str)
{
	char const *back_pat;
	char const *back_str;
 
	back_pat = NULL;
	while (1) 
	{
		if (*pat == '*' && *(pat + 1) == '\0' || (!*str && !*pat))
				return true;
		if (*pat == '*')
		{
			back_pat = ++pat;
			back_str = str;
			continue ;
		}
		if (*str == *pat)
		{
			pat++;
			str++;
			continue ;
		}
		if (*str == '\0' || !back_pat)
			return false;
		pat = back_pat;
		str = ++back_str;
	}
}

int	main(int argc, char **argv)
{
	
	if (argc > 2)
		printf("patern: %s, str: %s = %d\n", argv[1], argv[2], glob_match2(argv[1], argv[2]));
	return (0);
}