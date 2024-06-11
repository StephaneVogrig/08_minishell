/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:59:12 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:55:00 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H

# include "parse_utils.h"
# include "input_to_pipelist_bonus.h"
# include "pipelist_bonus.h"

char	*parse(char *input, t_cmd **cmd, t_cmd **pipeline);

#endif
