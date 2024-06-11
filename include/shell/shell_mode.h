/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mode.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:31:07 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 17:19:26 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_MODE_H
# define SHELL_MODE_H

# include <readline/readline.h>
# include "environment.h"

t_bool	shell_mode_init_interactive(t_env **env);
t_bool	shell_mode_init_file(t_env **env);
t_bool	shell_mode_is_interactive(t_env *env);

#endif
