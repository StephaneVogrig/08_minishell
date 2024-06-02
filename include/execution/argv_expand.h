/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_expand.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:08:13 by stephane          #+#    #+#             */
/*   Updated: 2024/06/02 20:21:50 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef ARGV_EXPAND_H
# define ARGV_EXPAND_H

# include "expand_and_dequote.h"

t_bool	argv_expand(t_list **argvlist, t_env *env);

#endif