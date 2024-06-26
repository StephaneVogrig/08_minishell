/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish_free.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:58:30 by stephane          #+#    #+#             */
/*   Updated: 2024/06/18 17:52:45 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_FREE_H
# define MINISH_FREE_H

# include "libft.h"
# include "command.h"
# include "environment.h"

void	minishell_free(t_cmd *data, char *str, char **argv, t_env *env);

#endif
