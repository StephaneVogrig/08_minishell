/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:50:36 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 16:55:01 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stdio.h>
# include "libft.h"
# include "char.h"

char		*skip_blank(char *str);
t_bool		strlist_add_str(t_list **strlist, char *str);
char		**strlist_to_strtab(t_list *strlist);
t_char_m	*mini_strndup(char *str, int n);
t_char_m	*mini_strdup(char *str);
char		*end_quote(char *str);
t_bool		is_empty(char *str);

#endif
