/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_alone.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:22:07 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/26 23:43:34 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// t_env	*envp_to_env_v2(char **envp)///possible de modifier envp_to_env ?
// {
// 	t_env	*env;
// 	t_env	*node;

// 	if (!envp)
// 		return (NULL);
// 	node = NULL;
// 	env = NULL;
// 	while (*envp)
// 	{
// 		node = malloc(sizeof(*node));
// 		if (!node)
// 		{
// 			env_free(env);
// 			return (NULL);
// 		}
// 		if (node_init_v2(node, *envp) == FAILURE)
// 		{
// 			env_free(env);
// 			return (NULL);
// 		}
// 		env_add_back(&env, node);
// 		envp++;
// 	}
// 	return (env);
// }

void	env_sorted_display(t_env *env)
{
	while (env != NULL)
	{
		if(env->type == EXPORTED)
		{
			// if (env->name[0] != '_' && env->name[1] != '\0')
			// 	printf("declare -x %s=\"%s\"\n", env->name, env->value);
			if (env->name[0] == '_' && env->name[1] == '\0')
				env = env->next;
			else
			{	
				printf("declare -x %s=\"%s\"\n", env->name, env->value);
				env = env->next;
			}	
		}
		else
		{
			printf("declare -x %s\n", env->name);
			env = env->next;
		}
	}
}

void	strtab_print(char **tabstr)////////
{
	// printf("--> tabstr=%p\n", tabstr);
	if (tabstr == NULL)
		return ;
	while (*tabstr)
	{
		ft_putstr_fd(*tabstr, STDOUT_FD);
		write(STDOUT_FD, "\n", 1);
		tabstr++;
	}
}

int	tab_to_lst(char **sorted_tab)
{
	t_env	*sorted_env;
	
	sorted_env = envp_to_env(sorted_tab);
	if (!sorted_env)
		return (ENOMEM);
	env_sorted_display(sorted_env);//enleve pour debug
	env_free(sorted_env);
	return (0);
}

int	strtab_sort(char **to_sort)
{
	int		i;
	char	*temp;
	int		count;

	count = 0;
	temp = NULL;
	i = 1;
	while (to_sort[i])
	{
		if (ft_strcmp(to_sort[i - 1], to_sort[i]) > 0)
		{
			temp = to_sort[i];
			to_sort[i] = to_sort[i - 1];
			to_sort[i - 1] = temp;
			count++;
		}
		i++;
	}
	if (count == 0)
		return (tab_to_lst(to_sort));
	else
		strtab_sort(to_sort);
	return (0);
}




char	**env_to_envp_export(t_env *env, int size)
{
	char	**envp;
	int		i;

	i = 0;
	
	// printf("--> size=%d\n", size);
	envp = ft_calloc(size + 1, sizeof(*envp));
	// printf("envp-> %p\n", envp);
	if (!envp)
		return (NULL);
	while(env)
	{
		// if (env->name[0] == '_' && env->name[1] == '\0')
		// 	env = env->next;
		
		if (env->type == INTERNAL)
		{
			// printf("INTERNAL: %s_\n", env->name);
			env = env->next;
		}
		else
		{
			// printf("env->name: %s_\n", env->name);
			if (env->type == EXPORTED && env->value[0] != '\0')
			{
				// envp[i] = env_join(env->name, env->value);
				envp[i] = ft_strjoin(env->name, "=");
				envp[i] = ft_strjoin_free_s1(envp[i], env->value);
				//  printf("EXPORTED+VALUE envp[i]=%s\n", envp[i]);
			}
			else if (env->type == EXPORTED && env->value[0] == '\0')
			{
				envp[i] = ft_strjoin(env->name, "=");
				//  printf("EXPORTED_EMPTY envp[i]=%s\n", envp[i]);
			}
			else if (env->type == NO_VALUE)
			{
				envp[i] = ft_strdup(env->name);
				//  printf("NO_VALUE envp[i]=%s\n", envp[i]);
			}
			if (!envp[i])
			{
				i--;
				// printf("free\n");
				// strtab_free(envp);
				// return (NULL);
			}
			// printf("env->name: %s\n", env->name);
			// printf("env->type: %d\n", env->type);
			// printf("envp[i]: %s\n", envp[i]);
			// printf("i=%d\n", i);	
			i++;
			env = env->next;
		}
			
	}
	// printf("////////// TAB /////////////\n");
	// strtab_print(envp);
	// printf("////////////////////////////\n");
	return (envp);
}
// char	**env_to_envp_export(t_env *env, int size)
// {
// 	char	**envp;
// 	int		i;
	
// 	i = 0;
// 	// printf("size=%d\n", size);
// 	envp = calloc(size + 1, sizeof(*envp));
// 	if (!envp)
// 		return (NULL);
// 	while (env)//(i < size )//
// 	{
// 		// if (env->name[0] == '_' && env->name[1] == '\0')
// 		// 	env = env->next;
// 		if (env->type == INTERNAL)
// 			env = env->next;
// 		else
// 		{
// 			if (env->type == EXPORTED && env->value[0] != '\0')
// 				envp[i] = env_join(env->name, env->value);
// 			else if (env->type == EXPORTED && env->value[0] == '\0')
// 				envp[i] = ft_strjoin(env->name, "=");
// 			else if (env->type == NO_VALUE)
// 				envp[i] = ft_strdup(env->name);
// 			if (!envp[i])
// 			{
// 				strtab_free(envp);
// 				return (NULL);
// 			}
// 			// printf("i=%d\n", i);
// 			env = env->next;
// 			i++;
// 		}
// 	}
// 	// printf("////////// TAB /////////////\n");
// 	// strtab_print(envp);
// 	// printf("////////////////////////////\n");
// 	return (envp);
// }

int	display_envp_sorted(t_env *envp)
{
	char **tab_to_sort;
	
	tab_to_sort = env_to_envp_export(envp, env_size(envp, ALL));
	if(strtab_sort(tab_to_sort) == ENOMEM)
	{
		perror("minishell: export");
		strtab_free(tab_to_sort);
		return (ENOMEM);
	}
	strtab_free(tab_to_sort);
	return (0);
}