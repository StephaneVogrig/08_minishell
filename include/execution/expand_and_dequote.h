/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_dequote.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:15:32 by stephane          #+#    #+#             */
/*   Updated: 2024/06/02 20:17:36 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef EXPAND_AND_DEQUOTE_H
# define EXPAND_AND_DEQUOTE_H

# include "buff.h"
# include "parse.h"

t_bool	expand_and_dequote(char *str, t_list **strlist, t_env *env);

#endif