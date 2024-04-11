/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:55 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/11 22:35:37 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "environment.h"
# include "libft.h"

// # include "memory.h"
// # include <stddef.h>
// # include <stdlib.h>

char	**builtin_unset(char **envp, char *str);

#endif