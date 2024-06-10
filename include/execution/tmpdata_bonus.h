/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmpdata_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:09:03 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/10 02:34:26 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPDATA_BONUS_H
# define TEMPDATA_BONUS_H

# include "buff.h"
# include "wildcard_bonus.h"
# include "ft_constant.h"

typedef struct s_tmpdata{
	t_buff		buffer;
	t_buff		format;
	t_wildcard	wc;
}	t_tmpdata;

void	data_init(t_tmpdata *data);
void	data_clear(t_tmpdata *data);
t_bool	data_add_char(t_tmpdata *data, char c);
t_bool	data_add_str(t_tmpdata *data, char *str);
t_bool	data_add_str_n(t_tmpdata *data, char *str, int n);

#endif