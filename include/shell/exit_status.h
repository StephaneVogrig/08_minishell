/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:12:38 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/18 15:35:04 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

# include "environment.h"

t_bool	exit_status_create(t_env *env);
t_bool	exit_status_set(int value, t_env *env);
inline char	*exit_status_get_str(t_env *env);

#endif