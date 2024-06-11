/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlink.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:03:23 by stephane          #+#    #+#             */
/*   Updated: 2024/04/26 18:14:05 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef STRLINK_H
# define STRLINK_H

#include <stdlib.h>
#include "libft.h"
#include "vs_type.h"

typedef struct s_strlink{
	char				*str;
	int					len;
	struct s_strlink	*next;
}	t_strlink;

typedef t_strlink t_strlink_m;

void		strlink_init(t_strlink *strlink, char *str, int len, t_strlink *next);
t_strlink_m	*strlink_add_new(t_strlink *strlink);
int			strlink_len(t_strlink *strlink);
void		strlink_fill_str(char *str, t_strlink *strlink);
t_char_m	*strlink_to_str(t_strlink *strlink);
void		strlink_clear(t_strlink *strlink);

#endif
