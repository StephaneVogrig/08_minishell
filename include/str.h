/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:50:36 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/06 15:47:26 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stdio.h>
# include "libft.h"

t_bool		is_blank(char c);
t_bool		is_operator(char c);
char		*skip_blank(char *str);
void		pipex_strncpy(char *dest, char *src, int n);
t_bool		add_to_strlist(t_list **strlist, char *str);
char		**strlist_to_strtab(t_list *strlist);
t_char_m	*mini_strndup(char *str, int n);
t_char_m	*mini_strdup(char *str);

#endif
