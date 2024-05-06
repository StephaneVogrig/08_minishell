/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 04:48:37 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/06 17:19:19 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PATH_H
# define CMD_PATH_H

# include "redirection.h"
# include "str.h"
# include "environment.h"
# include "exit.h"

char	*cmd_path(char **argv, t_env *envp);

#endif