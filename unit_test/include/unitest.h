/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unitest.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:08:22 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/04 18:06:58 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNITEST_H
# define UNITEST_H

# include "builtin.h"
# include "environment.h"
# include "libft.h"
# include <errno.h>
# include <stdio.h>

void	env_dup_test(char **argv, char **envp);
void	env_get_test(void);
void	builtin_unset_test(void);
void	builtin_export_test(void);
// void	builtin_export_alone_test(char **strtab);//pour test avec envp
void	builtin_export_alone_test(void);
void	builtin_env_test(void);
void	builtin_cd_test(char **env);
void	env_shlvl_test(char **env);

#endif