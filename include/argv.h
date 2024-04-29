/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 05:46:02 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/29 05:51:53 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGV_H
# define ARGV_H

# include "libft.h"
# include "buff.h"
# include "str.h"

t_bool	argv_add_buffer(t_list **argv, t_buff *buffer);

#endif