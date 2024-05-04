/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:16:08 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/04 00:25:13 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_redir(t_redir *redir)
{
	char	type[4][10] = {"in", "out apd", "out trc", "hd"};

	if (!redir)
		ft_printf("redir %p\n", redir);
	while (redir)
	{
		// ft_printf("redir\n");
		ft_printf("redir type:%s, name:%s\n", type[redir->type],
			redir->file_name);
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

void	strlink_print(t_strlink *strlink)
{
	while (strlink)
	{
		ft_printf("str:%s, len:%i\n", strlink->str, strlink->len);
		strlink = strlink->next;
	}
}

void	print_pipeline(t_cmd *pipeline)
{
	while (pipeline)
	{
		print_cmd(*pipeline);
		pipeline = pipeline->next;
	}
}

void	display_argv_lst(t_list *lst)
{
	if (lst == NULL)
	{
		ft_printf("argv is null \n");
		return ;
	}
	while (lst != NULL)
	{
		ft_printf("-> %s \n", lst->content);
		lst = lst->next;
	}
}

void	display_redir_lst(t_redir *lst)
{
	if (lst == NULL)
	{
		ft_printf("redir is null \n");
		return ;
	}
	while (lst != NULL)
	{
		ft_printf("-> %s \n", lst->file_name);
		lst = lst->next;
	}
}
void	display_t_cmd(t_cmd *cmd)
{
	t_list *heredoc;
	t_redir *redir;
	t_list *argv;

	if (cmd == NULL)
	{
		ft_printf("cmd is null \n");
		return ;
	}
	heredoc = cmd->heredoc;
	argv = cmd->argv;
	redir = cmd->redir;
	printf("t_cmd ARGV--------------\n");
	display_argv_lst(argv);
	printf("t_cmd HEREDOC--------------\n");
	display_argv_lst(heredoc);
	printf("t_cmd REDIR--------------\n");
	display_redir_lst(redir);
}