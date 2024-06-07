/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:21:01 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/07 11:38:22 by svogrig          ###   ########.fr       */
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
void	print_pipeline(t_cmd *pipeline, char *color);
void	display_t_cmd(t_cmd *cmd);
void	print_pipelist(t_cmd *pipelist, char *color, char *pipeline_color);

#endif