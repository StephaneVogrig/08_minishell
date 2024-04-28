/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:05:15 by stephane          #+#    #+#             */
/*   Updated: 2024/04/27 19:45:55 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef EXPANSE_H
# define EXPANSE_H

# include "libft.h"
# include "str.h"
# include "buff.h"
# include "token.h"
# include "environment.h"

char	*expanse_exit_status(t_buff *buffer, char *str, int *exit_status);
char	*expanse_quoted(t_buff *buffer, char *str, char **env, int *exit_status);
char	*expanse_unquoted(t_buff *buffer, char *str, t_list **argv, char **env);

#endif