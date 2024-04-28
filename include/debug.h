/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:21:01 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/26 16:40:47 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef DEBUG_H
# define DEBUG_H

#include "libft.h"
#include "command.h"
#include "strlink.h"

void	print_redir(t_redir *redir);
void	print_cmd(t_cmd cmd);
void	strlink_print(t_strlink *strlink);
void	print_pipeline(t_cmd *pipeline);

#endif