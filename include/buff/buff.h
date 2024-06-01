/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 01:13:55 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/31 16:39:24 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include "libft.h"
# include "buffsave.h"

typedef struct s_buff{
	char		data[BUFFER_SIZE];
	int			offset;
	t_buffsave	*save_head;
	t_buffsave	*save_last;
}	t_buff;

void		buff_init(t_buff *buffer);
void		buff_clear(t_buff *buffer);
int			buff_len(t_buff *buffer);
t_char_m	*buff_to_str(t_buff *buffer);

t_bool		buff_add_char(t_buff *buffer, char c);
t_bool		buff_add_str(t_buff *buffer, char *str);
t_bool		buff_add_str_n(t_buff *buffer, char *str, int n);

#endif
