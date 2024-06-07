/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 20:16:08 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/07 11:45:47 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

#define GOLD "\033[38;2;255;176;0m"
#define DODGERBLUE "\033[38;5;33m"
# define RED "\033[31m"
# define GREEN "\033[32m"
#define RESET "\033[0m"

void	print_redir(t_redir *redir)
{
	char	*type;

	if (!redir)
		ft_printf("%sredir: %s(empty)\n", GOLD, RESET);
	while (redir)
	{
		if (redir->type & EXPANSE)
			type = "HEREDOC EXPANSE";
		else if (redir->type & HEREDOC)
			type = "HEREDOC NO EXPANSE";
		else if (redir->type & IN)
			type = "IN";
		else if (redir->type & APPEND)
			type = "OUT APPEND";
		else
			type = "OUT TRUNC";
		ft_printf("%sredir type: %s%s%s\n", GOLD, DODGERBLUE, type, RESET);
		ft_printf("%s      name: %s%s\n", GOLD, RESET, redir->str);
		redir = redir->next;
	}
}


void	strlink_print(t_strlink *strlink)
{
	while (strlink)
	{
		ft_printf("str:%s, len:%i\n", strlink->str, strlink->len);
		strlink = strlink->next;
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
		ft_printf("-> %s \n", lst->str);
		lst = lst->next;
	}
}

void	display_t_cmd(t_cmd *cmd)
{
	t_redir *redir;
	t_list *argv;

	if (cmd == NULL)
	{
		ft_printf("cmd is null \n");
		return ;
	}
	argv = cmd->argv;
	redir = cmd->redir;
	printf("t_cmd ARGV--------------\n");
	display_argv_lst(argv);
	printf("t_cmd REDIR--------------\n");
	display_redir_lst(redir);
}

void	print_cmd(t_cmd *cmd)
{
	t_list	*current;

	if (cmd->flag == SUB)
	{
		ft_printf("flag SUB\n");
		print_pipelist(cmd->pipeline, GOLD, DODGERBLUE);
		return ;
	}

	print_redir(cmd->redir);
	ft_printf("%sargv:%s ", GOLD, RESET);
	// strlist_print_fd(cmd->argv, STDOUT_FD);
	current = cmd->argv;
	if (!current)
	{
		ft_putstr_fd("(empty)\n", STDOUT_FD);
		return ;
	}
	ft_printf("%s\n", current->content);
	current = current->next;
	while (current)
	{
		ft_printf("      %s\n", current->content);
		current = current->next;
	}
}

void	print_pipeline(t_cmd *pipeline, char *color)
{
	if (!color)
		color =  GOLD;
	ft_printf("%s************* pipeline *****************"RESET"\n", color);
	while (pipeline)
	{
		print_cmd(pipeline);
		if (pipeline->next)
			ft_printf("%s**********************************"RESET"\n", color);
		pipeline = pipeline->next;
	}
	ft_printf("%s*************** fin ***************"RESET"\n", color);
}


void print_pipelist(t_cmd *pipelist, char *color, char *pipeline_color)
{
	if (!color)
		color =  RED;
	if (!pipeline_color)
		pipeline_color =  DODGERBLUE;
	ft_printf("%s############ pipelist ###########   flag: ",color );
	while (pipelist)
	{
		if (!pipelist->previous)
			ft_printf("%i"RESET"\n" , pipelist->flag);
		else
			ft_printf("%s##################################   flag: %i"RESET"\n",color , pipelist->flag);

		print_pipeline(pipelist->pipeline, pipeline_color);
		
		pipelist = pipelist->next;
		// if (pipelist)
		// 	ft_printf(GOLD"#############################"RESET"\n");
	}
		ft_printf("%s############ fin ###########"RESET"\n", color);

}
