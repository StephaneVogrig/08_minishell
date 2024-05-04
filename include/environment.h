/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:00:39 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/04 22:35:22 by svogrig          ###   ########.fr       */
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
# define NO_VALUE 2
# define ALL 3

typedef struct s_env
{
	int				type;
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef t_env t_env_m;

// LIST_UTILS ----------------
t_env				*env_get_node_n(t_env *env, char *str, int n);
void				lst_node_del(t_env **env, t_env *node);
int					env_lst_size(t_env *env, int type);
void				display_the_list(t_env *env, int type);
void				lst_add_back(t_env **env, t_env *node);

// ENV_UTILS----------------
void				env_node_free(t_env *node);
void				env_free(t_env *env);
t_bool				node_init(t_env *node, char *str, int type);
char				*create_HOME_path(t_env *env);
void				node_HOME_cpy(t_env *env);

// ENVIRONMENT ----------------
t_env				*env_dup(char **envp);
char				*env_get(t_env *env, char *str);
char				*env_get_n(t_env *env, char *str, int n);
char				*env_join(char *name, char *value);
char				**env_to_envp(t_env *env);

// ENV_SHLVL -----------------
void				init_shlvl(t_env *env);
#endif
