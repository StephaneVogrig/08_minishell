/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlink.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:00:19 by stephane          #+#    #+#             */
/*   Updated: 2024/04/26 18:29:29 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "strlink.h"

void	strlink_init(t_strlink *strlink, char *str, int len, t_strlink *next)
{
	strlink->str = str;
	strlink->len = len;
	strlink->next = next;
}

t_strlink_m	*strlink_add_new(t_strlink *strlink)
{
	t_strlink_m	*new;
	
	new = ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	strlink->next = new;
	return (new);
}

int	strlink_len(t_strlink *strlink)
{
	int	len;
	
	len = 0;
	while (strlink)
	{
		len += strlink->len;
		strlink = strlink->next;
	}
	return (len);
}

void	strlink_fill_str(char *str, t_strlink *strlink)
{
	while (strlink)
	{
		ft_memcpy(str, strlink->str, strlink->len);
		str += strlink->len;
		strlink = strlink->next;
	}
	*str = '\0';
}

t_char_m	*strlink_to_str(t_strlink *strlink)
{
	t_char_m	*str;

	str = malloc(strlink_len(strlink) + 1);
	if (!str)
		return (NULL);
	strlink_fill_str(str, strlink);
	return (str);
}

void	strlink_clear(t_strlink *strlink)
{
	t_strlink	*temp;
	t_strlink	*current;

	current = strlink->next;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	strlink_init(strlink, NULL, 0, NULL);
}
