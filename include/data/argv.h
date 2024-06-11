/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 05:46:02 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:55:22 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGV_H
# define ARGV_H

# include "libft.h"
# include "buff.h"

t_bool	strlist_add_str(t_list **strlist, char *str);
t_bool	strlist_add_buffer(t_list **argv, t_buff *buffer);
char	**argvlist_to_argvtab(t_list **argvlist);

#endif
