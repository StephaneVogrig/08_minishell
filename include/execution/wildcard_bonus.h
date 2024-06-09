/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:48:10 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/09 22:33:04 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_BONUS_H
# define WILDCARD_BONUS_H

# include "libft.h"
# include <dirent.h>

typedef struct s_wildcard {
	t_list	*list;
	int		flags;

}	t_wildcard;

/* flags */
# define WILDCARD_FIRST 1
# define WILDCARD_LAST 2

t_bool	wildcard_format_to_list(char *format, t_list **strlist);

/* wildcard_uils_bonus.c ******************************************************/

void			wc_free(t_wildcard *wc);
char			*mini_strstr(const char *big, const char *little);
int				ft_strcmp_rev(const char *big, const char *little);

#endif