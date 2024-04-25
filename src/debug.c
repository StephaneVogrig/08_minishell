/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:16:08 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/25 21:25:53 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "debug.h"

void	print_redir(t_redir *redir)
{
	char	type[4][10] = {"in", "out apd", "out trc", "hd"};
	
	if (!redir)
		ft_printf("redir %p\n", redir);
	while (redir)
	{
		// ft_printf("redir\n");
		ft_printf("%s, %s\n", type[redir->type], redir->file_name);
		redir = redir->next;
	}

}

void	print_cmd(t_cmd cmd)
{
	print_redir(cmd.redir);
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
