/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:16:08 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/06 21:05:25 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_cmd(t_cmd cmd)
{
	ft_printf("in: %s\n", cmd.in);
	ft_printf("out: %s\n", cmd.out);
	ft_printf("append_out: %s\n", cmd.append_out ? "oui" : "non");
	ft_printf("argv:\n");
	strlist_print_fd(cmd.argv, STDOUT_FD);
	ft_printf("------------------\n");
}

void	print_pipeline(t_cmd *pipeline)
{
	while (pipeline)
	{
		print_cmd(*pipeline);
		pipeline = pipeline->next;
	}
}
