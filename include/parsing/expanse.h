/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:05:15 by stephane          #+#    #+#             */
/*   Updated: 2024/05/19 17:16:38 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSE_H
# define EXPANSE_H

# include "str.h"
# include "argv.h"
# include "environment.h"

char	*end_name(char *str);
char	*expanse_exit_status(t_buff *buffer, char *str, t_env *env);
char	*expanse_quoted(t_buff *buffer, char *str, t_env *env);
char	*expanse_unquoted(t_buff *buffer, char *str, t_list **argv, t_env *env);

#endif