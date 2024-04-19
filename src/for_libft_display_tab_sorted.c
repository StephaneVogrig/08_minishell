/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tab_sorted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:22:07 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/18 22:22:31 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_strcmp_export(const char *s1, const char *s2)
{
	while ((*s1 || *s2) && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
void	export_alone(char **tab)
{
	int		i;
	char	**tab_sorted;
	char	*temp;
	int		count;

	count = 0;
	temp = NULL;
	// tab_sorted = mem_calloc(ft_strtab_size(tab) + 1, sizeof(char **));
	tab_sorted = tab;
	i = 1;
	while (tab[i])
	{
		if (ft_strcmp_export(tab[i - 1], tab[i]) > 0)
		{
			temp = tab[i];
			tab[i] = tab[i - 1];
			tab[i - 1] = temp;
			count++;
		}
		i++;
	}
	if (count == 0)
	{
		strtab_print(tab);
		return ;
	}
	else
		export_alone(tab);
}
