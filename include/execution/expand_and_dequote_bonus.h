/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_dequote_bonus.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 01:39:43 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 02:55:34 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_AND_DEQUOTE_BONUS_H
# define EXPAND_AND_DEQUOTE_BONUS_H

# include "tmpdata_bonus.h"
# include "expanse.h"

t_bool	expand_and_dequote(char *str, t_list **strlist, t_env *env);

/* expand_utils ***************************************************************/

char	*expanse_special_parameter(t_tmpdata *data, char *str, t_env *env);
char	*expanse_quoted(t_tmpdata *data, char *str, t_env *env);
char	*expand_spl_quoted(t_tmpdata *data, char *str);
char	*expand_dbl_quoted(t_tmpdata *data, char *str, t_env *env);
t_bool	data_buffer_to_wclist(t_tmpdata *data);

/* expand_and_dequote_utils_bonus *********************************************/

t_bool	select_with_data(t_tmpdata *data, t_list **strlist);

#endif

