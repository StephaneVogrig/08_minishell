/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:00:39 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/27 16:32:57 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "libft.h"
# include <stddef.h>
# include <stdlib.h>
# include "memory.h"

char	**env_dup(char **envp);
char	*env_get(char **env, char *str);
char	*env_get_n(char **env, char *str, int n);

#endif
