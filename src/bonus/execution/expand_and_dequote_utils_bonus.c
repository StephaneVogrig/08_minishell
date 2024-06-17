/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_dequote_utils_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 02:52:39 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/16 20:30:46 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "expand_and_dequote_bonus.h"

t_bool	wildcard_expand_to_strlist(t_tmpdata *data, t_list **strlist)
{
	t_list	*paths;

	paths = NULL;
	if (wildcard_select(&data->wc, &paths) == FAILURE)
		return (FAILURE);
	if (paths)
	{
		sort_strlist(&paths);
		ft_lstadd_back(strlist, paths);
	}
	else
		if (strlist_add_buffer(strlist, &data->format) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

t_bool	select_with_data(t_tmpdata *data, t_list **strlist)
{
	if (data->wc.flags != 0 || data->wc.list != NULL)
	{
		if (wildcard_expand_to_strlist(data, strlist) == FAILURE)
			return (FAILURE);
	}
	else if (strlist_add_buffer(strlist, &data->buffer) == FAILURE)
		return (FAILURE);
	data_clear(data);
	return (SUCCESS);
}
