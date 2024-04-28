/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:00:39 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/28 21:51:44 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "libft.h"
# include "memory.h"
# include <stddef.h>
# include <stdlib.h>

# define INTERNAL 0
# define EXPORTED 1

typedef struct s_env
{
	int				type;
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

t_env				*env_dup(char **envp);

// char				**env_dup(char **envp);
char				*env_get(char **env, char *str);
char				*env_get_n(char **env, char *str, int n);

#endif
