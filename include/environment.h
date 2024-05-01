/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:00:39 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/02 00:42:06 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "libft.h"
# include "memory.h"
# include <stddef.h>
# include <stdlib.h>

# define INTERNAL 0
# define EXPORTED 1 // can be unset
# define NO_VALUE 2 // can be unset
# define ALL 3      // to get both EXPORTED and NO_VALUE variables
# define PWD 4

typedef struct s_env
{
	int				type;
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

// LIST_UTILS ----------------
t_env				*env_get_node_n(t_env *env, char *str, int n);
void				lst_node_del(t_env **env, t_env *node);
int					env_lst_size(t_env *env, int type);
void				display_the_list(t_env *env, int type);
void				lst_add_back(t_env **env, t_env *node);

// ENVIRONMENT ----------------
void				env_node_free(t_env *node);
void				env_free(t_env *env);
t_bool				node_init(t_env *node, char *str, int type);
t_env				*env_dup(char **envp);
char				*env_get(t_env *env, char *str);
char				*env_get_n(t_env *env, char *str, int n);
char				*env_join(char *name, char *value);
char				**env_to_envp(t_env *env);

#endif
