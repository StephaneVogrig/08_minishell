/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:07:07 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/11 17:02:23 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unitest.h"

int	main(int argc, char **argv, char **envp)
{
	// env_dup_test(argv, envp);
	// env_get_test();
	builtin_unset_test();
	return (0);
}
