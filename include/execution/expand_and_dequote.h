/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_dequote.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:15:32 by stephane          #+#    #+#             */
/*   Updated: 2024/06/03 16:35:15 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_AND_DEQUOTE_H
# define EXPAND_AND_DEQUOTE_H

# include "buff.h"
# include "parse.h"

t_bool	expand_and_dequote(char *str, t_list **strlist, t_env *env);

#endif