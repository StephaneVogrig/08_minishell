/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unitest.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:08:22 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/10 23:46:15 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNITEST_H
# define UNITEST_H

# include <errno.h>
# include <stdio.h>
# include "environment.h"
# include "libft.h"

void	env_dup_test(char **argv, char **envp);
void	env_get_test(void);

#endif