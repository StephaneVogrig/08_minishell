/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 02:50:36 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/06 19:10:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H

# include <stdio.h>
# include "libft.h"
# include "exit.h"

t_bool	is_blank(char c);
char	*skip_blank(char *str);
void	pipex_strncpy(char *dest, char *src, int n);
t_bool	add_to_strlist(t_list **strlist, char *str);
char	**argv_empty(void);

#endif
