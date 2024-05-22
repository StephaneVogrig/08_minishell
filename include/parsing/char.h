/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 06:17:31 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/22 17:15:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_H
# define CHAR_H

# include "libft.h"

t_bool	is_meta(char c);
t_bool	is_blank(char c);
t_bool	is_operator(char c);
t_bool	is_special_parameter(char c);

#endif