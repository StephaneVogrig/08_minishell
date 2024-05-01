/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 21:01:51 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/01 21:12:27 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_UTILS_H
# define LST_UTILS_H

# include "environment.h"

// LIST_UTILS ----------------
t_env	*env_get_node_n(t_env *env, char *str, int n);
void	lst_node_del(t_env **env, t_env *node);
int		env_lst_size(t_env *env, int type);
void	display_the_list(t_env *env);
void	lst_add_back(t_env **env, t_env *node);

#endif