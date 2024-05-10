/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:05:15 by stephane          #+#    #+#             */
/*   Updated: 2024/05/10 16:43:44 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef EXPANSE_H
# define EXPANSE_H

# include "str.h"
# include "argv.h"
# include "environment.h"

char	*end_name(char *str);
char	*expanse_exit_status(t_buff *buffer, char *str, int *exit_status);
char	*expanse_quoted(t_buff *buffer, char *str, t_env *env, int *exit_status);
char	*expanse_unquoted(t_buff *buffer, char *str, t_list **argv, t_env *env);

#endif