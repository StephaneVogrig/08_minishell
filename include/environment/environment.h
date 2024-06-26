/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:00:03 by smortemo          #+#    #+#             */
/*   Updated: 2024/06/09 23:26:11 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "libft.h"
# include "memory.h"
# include "str.h"
# include <errno.h>
# include <stddef.h>
# include <stdlib.h>

/* type */
# define INTERNAL 1
# define EXPORTED 2
# define NO_VALUE 3
# define ALL 4
# define DIR_ 5
# define DIR_NO_VAL 6

/* errors */
# define ENOEXIST 2

typedef struct s_env
{
	int				type;
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;
typedef t_env		t_env_m;

// ENV_UTILS ----------------
int					env_size(t_env *env, int type);
void				env_display(t_env *env, int type);

// ENV_PWD --------------------

t_bool				env_pwd_init(t_env **env);

// ENV_SHLVL -----------------
t_bool				env_shlvl_init(t_env **env);

// TILDE ---------------
char				*create_home_path(t_env *env);
int					node_home_cpy(t_env *env);

// ENV_GET --------------------
t_env				*env_get_node(t_env *env, char *str);
t_env				*env_get_node_n(t_env *env, char *str, int n);
char				*env_get_type(t_env *env, char *str, int type);
char				*env_get(t_env *env, char *str);
char				*env_get_n(t_env *env, char *str, int n);

// ENV_NODE --------------------
t_bool				node_init(t_env *node, char *str);
void				env_node_free(t_env *node);
void				env_node_del(t_env **env, t_env *node);
t_bool				var_init(t_env *node, char *str, int n);
int					export_new_node(t_env **env, char *str, int n);

// ENV_NODE2 ------------------
t_bool				env_node_set_value(char *value, t_env *node);
t_env				*env_node_new(char *name, char *value, int type);

// ENVP ----------------------
t_bool				envp_to_env(char **envp, t_env **env);
char				**env_to_envp(t_env *env);
char				*env_join(char *name, char *value);

// ENVIRONMENT ----------------
void				env_add_back(t_env **env, t_env *node);
void				env_free(t_env *env);
t_env				*env_init(char **envp);
int					env_set_value(char *name, char *value, t_env *env);
t_env				*env_add_new(char *name, char *value, int type,
						t_env **env);

// EXIT_STATUS -------------------
t_bool				exit_status_init(t_env **env);
void				exit_status_set(int value, t_env *env);
char				*exit_status_get_str(t_env *env);
int					exit_status_get_int(t_env *env);

#endif
