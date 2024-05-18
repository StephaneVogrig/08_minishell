/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mode.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:31:07 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/18 19:15:03 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_MODE_H
# define SHELL_MODE_H

#include "environment.h"

t_bool	shell_mode_init_interactive(t_env *env);
t_bool	shell_mode_init_file(t_env *env);
t_bool	shell_is_interactive(t_env *env);

#endif