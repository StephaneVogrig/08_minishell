/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:07:07 by smortemo          #+#    #+#             */
/*   Updated: 2024/04/28 21:54:19 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unitest.h"

int	main(int argc, char **argv, char **envp)
{
	env_dup_test(argv, envp);
	// env_get_test();
	// builtin_unset_test();
	// builtin_export_test();
	// builtin_export_alone_test();
	// builtin_env_test();
	return (0);
}
