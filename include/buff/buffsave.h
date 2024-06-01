/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffsave.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 03:36:13 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/31 16:40:20 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFSAVE_H
# define BUFFSAVE_H

# include "libft.h"

typedef struct	s_buff_save{
	char				data[BUFFER_SIZE];
	int					offset;
	struct s_buff_save	*next;
}	t_buffsave;

t_buffsave	*buffsave_new(void);
t_bool		buffsave_add_new(t_buffsave **save);
t_bool		buffsave_add_str(t_buffsave **save, char *str);
t_bool		buffsave_add_str_n(t_buffsave **save, char *str, int n);

#endif
