/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:21:01 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/06 04:18:09 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "command.h"
# include "libft.h"
# include "strlink.h"

void	print_redir(t_redir *redir);
void	print_cmd(t_cmd *cmd);
void	strlink_print(t_strlink *strlink);
void	print_pipeline(t_cmd *pipeline);
void	display_t_cmd(t_cmd *cmd);

#endif