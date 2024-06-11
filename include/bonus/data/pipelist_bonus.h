/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelist_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:19:55 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:54:35 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELIST_BONUS_H
# define PIPELIST_BONUS_H

# include "command.h"
# include "pipeline.h"

t_cmd	*pipelist_new(void);
void	pipelist_free(t_cmd *pipelist);

#endif
