/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:05:15 by stephane          #+#    #+#             */
/*   Updated: 2024/06/10 01:39:50 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSE_H
# define EXPANSE_H

# include "str.h"
# include "argv.h"
# include "environment.h"

char	*end_name(char *str);
t_bool	is_token_empty(char *str, t_env *env);

#endif
