/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_alone.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:22:07 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/18 22:22:31 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	display_tab_export(char **str, int i)
{
	while (str[i])
	{
		if (str[i][0] == '_' && str[i][1] == '=')
			break ;
		printf("declare -x %s", str[i]);
		i++;
		if (str[i] != NULL)
			printf("\"%s\"", str[i]);
		printf("\n");
		i++;
	}
	if(str[i] == NULL)
		return ;
	display_tab_export(str, i + 2);
}

void	modify_tab(char **sorted_tab)
{
	char	**tab_to_display;
	int		i;
	int		j;
	int		count;
	int		len;

	len = 2 * ft_strtab_size(sorted_tab);
	tab_to_display = (char **)malloc(sizeof(char *) * ((len) + 1));
	j = 0;
	i = 0;
	while (sorted_tab[j])
	{
		count = ft_strchr_i(sorted_tab[j], '=');
		if (count != 0)
		{
			tab_to_display[i] = ft_strndup(sorted_tab[j], count + 1);
			i++;
			tab_to_display[i] = ft_strdup(&sorted_tab[j][count + 1]);
		}
		else
		{
			tab_to_display[i] = ft_strdup(sorted_tab[j]);
			i++;
			tab_to_display[i] = NULL;
		}
		i++;
		j++;
	}
	tab_to_display[i] = NULL;
	display_tab_export(tab_to_display, 0);
	strtab_free(tab_to_display);
}

void	export_alone(char **envp)
{
	int		i;
	char	*temp;
	int		count;

	count = 0;
	temp = NULL;
	i = 1;
	while (envp[i])
	{
		if (ft_strcmp(envp[i - 1], envp[i]) > 0)
		{
			temp = envp[i];
			envp[i] = envp[i - 1];
			envp[i - 1] = temp;
			count++;
		}
		i++;
	}
	if (count == 0)
	{
		modify_tab(envp);
		return ;
	}
	else
		export_alone(envp);
}
