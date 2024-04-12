/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:37:55 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/12 15:28:23 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "environment.h"
# include "libft.h"

// # include "memory.h"
// # include <stddef.h>
// # include <stdlib.h>

int	ft_strtab_size(char **strtab); // ajouter dans libft ?
char	**builtin_unset(char **envp, char *str);
char	**builtin_export(char **envp, char *str);

#endif