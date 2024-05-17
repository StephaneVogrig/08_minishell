/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:15:30 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/17 21:44:12 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	mini_rand(int num, int i)
{
	int	mod;
	int	mult;

	mod = INT_MAX;
	mult = 48271;
	num = (mult * num + i) % mod;
	if (num < 0)
		num = -num;
	return (num);
}

char	*get_path_temp(void)
{
	int		num;
	int		i;
	char	*hdt;

	num = 12345;
	i = 0;
	while (1)
	{
		num = mini_rand(num, i);
		hdt = ft_itoa(num);
		if (!hdt)
			return (NULL);
		hdt = ft_strjoin_free_s2("/tmp/minishell_temp_", hdt);
		if (!hdt)
			return (NULL);
		if (access(hdt, F_OK) == -1)
			return (hdt);
		free(hdt);
		i++;
	}
	return (NULL);
}

int	heredoc_fill(t_redir *redir, t_env *env, int *exit_status)
{
	char	*path;
	int		fd;
	int		exit_code;

	path = get_path_temp();
	if (path == NULL)
		return (FAILURE);
	fd = open(path, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		free(path);
		return (FAILURE);
	}
	exit_code = heredoc_scan(fd, redir, env, exit_status);
	free(redir->str);
	redir->str = path;
	close(fd);
	return (exit_code);
}

int	heredoc_loop(t_cmd_m *cmdlist, t_env_m *env, int *exit_status)
{
	int		exit_code;
	t_redir	*redir;

	exit_code = SUCCESS;
	while (cmdlist)
	{
		redir = cmdlist->redir;
		while (redir)
		{
			if (redir->type & HEREDOC)
			{
				exit_code = heredoc_fill(redir, env, exit_status);
				if (exit_code != SUCCESS)
					break ;
			}
			redir = redir->next;
		}
		cmdlist = cmdlist->next;
	}
	return (exit_code);
}

t_bool	heredoc(t_cmd_m *cmdlist, t_env_m *env, int *exit_status)
{
	int		exit_code;
	int		fd;

	fd = dup(0);
	signal(SIGINT, handler_ctrl_c_heredoc);
	exit_code = heredoc_loop(cmdlist, env, exit_status);
	dup2(fd, 0);
	close(fd);
	if (exit_code != SUCCESS)
		pipeline_free(&cmdlist);
	signal(SIGINT, handler_ctrl_c_interactive);
	return (exit_code);
}
