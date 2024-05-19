/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:22:35 by stephane          #+#    #+#             */
/*   Updated: 2024/05/19 17:20:26 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include "expanse.h"

char	*parse_spl_quoted(t_buff *buffer, char *str);
char	*parse_dbl_quoted(t_buff *buffer, char *str, t_env *env);
char	*parse_unquoted(t_buff *buffer, char *str, t_list **argv, t_env *env);

#endif