/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:48:10 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/06 00:12:29 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_BONUS_H
# define WILDCARD_BONUS_H

# include "libft.h"
# include <dirent.h>

/* flags */
# define WILDCARD_FIRST 1
# define WILDCARD_LAST 2

typedef struct s_wildcard {
	t_list	*list;
	int		flags;

}	t_wildcard;

t_bool	wildcard_to_list(char *format, t_list **strlist);

#endif