/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 05:46:02 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/06 15:48:48 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGV_H
# define ARGV_H

# include "libft.h"
# include "buff.h"
# include "str.h"
// # include "exit.h"

t_bool	argv_add_buffer(t_list **argv, t_buff *buffer);
// char	**argv_empty(void);

#endif