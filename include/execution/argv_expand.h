/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_expand.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:08:13 by stephane          #+#    #+#             */
/*   Updated: 2024/06/11 14:55:34 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGV_EXPAND_H
# define ARGV_EXPAND_H

# include "expand_and_dequote.h"

t_bool	argv_expand(t_list **argvlist, t_env *env);

#endif
