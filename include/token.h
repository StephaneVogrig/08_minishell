/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 19:16:27 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/27 19:44:00 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"
# include "str.h"
# include "strlink.h"
# include "parse.h"

char	*next_token(char *str, char	**token);
char	*add_next_token(char *str, t_list **tokenlist, char **env, int *exit_status);
t_bool	argv_add_buffer(t_list **argv, t_buff *buffer);

#endif