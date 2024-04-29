/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:00:39 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/30 01:07:01 by smortemo         ###   ########.fr       */
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
void				env_free(t_env *env);
void				display_the_list(t_env *env);

char				*env_get(t_env *env, char *str);
char				*env_get_n(t_env *env, char *str, int n);

char				**env_to_envp(t_env *env);

void				env_node_del(t_env **env, t_env *node);

#endif
