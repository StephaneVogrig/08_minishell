/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_dequote.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 20:15:32 by stephane          #+#    #+#             */
/*   Updated: 2024/06/09 23:10:40 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_AND_DEQUOTE_H
# define EXPAND_AND_DEQUOTE_H

# include "buff.h"
# include "expanse.h"

t_bool	expand_and_dequote(char *str, t_list **strlist, t_env *env);

/* expand_utils ***************************************************************/

char	*expand_spl_quoted(t_buff *buffer, char *str);
char	*expand_dbl_quoted(t_buff *buffer, char *str, t_env *env);
t_bool	is_token_empty(char *str, t_env *env);

#endif