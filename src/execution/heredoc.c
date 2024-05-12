/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:15:30 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/12 19:58:07 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

# include "heredoc.h"

int	mini_rand(int num, int i)
{
	int mod;
	int mult;

	mod = INT_MAX;//128
	mult = 48271;//7
	num = (mult * num + i) % mod;
	if(num < 0)
        num = -num;
	return(num);
}

char	*get_path_temp()
{
	int num;
	int i;
	char *hdt;

	num = 12345; //peut etre la valeur de SYSTEMD_EXEC_PID (env)
	i = 0;
	while(1)
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

char	*heredoc_expanse(int fd, char *str,t_env *env, int *exit_status)
{
	char	*end;
	char	*expand;
	int		i;

	if (*str == '?')
	{
		expand = ft_itoa(*exit_status);
		if (!expand)
			return (NULL);
		ft_putstr_fd(expand, fd);
		free (expand);
		return (str + 1);
	}
	end = end_name(str);
	i = end - str;
	if (i == 0)
	{
		write(fd, "$", 1);
		return (str);
	}
	str = env_get_n(env, str, i);
	ft_putstr_fd (str, fd);
	return (end);
}

void	heredoc_save_expanse(int fd, char *input, t_env *env, int *exit_status)
{
	int	i;

	i = 0;;
	while (1)
	{
		if (!input[i])
		{
			write(fd, input, i);
			write(fd, "\n", 1);
			break ;
		}
		if (input[i] == '$')
		{
			write(fd, input, i);
			input = heredoc_expanse(fd, &input[i + 1], env, exit_status);
			i = 0;
			continue ;
		}
		i++;
	}
}

int	heredoc_scan(int type, char *limiter, int fd, t_env *env, int *exit_status)
{
	char	*input;
	extern int	g_global;

	while (1)
	{
			// ft_printf("new input\n");
		input = readline(">");
		if (g_global == SIGINT)
		{
			g_global = 0;
			free(input);
			return (130);
		}
		if (!input) //ctrl-d
		{
			fd_printf(STDERR_FD, "minishell: warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (ft_strcmp(input, limiter) == 0)
		{
			free(input);
			break;
		}
		if (type & EXPANSE)
			heredoc_save_expanse(fd, input, env, exit_status);
		else
			fd_printf(fd, "%s\n", input);
		free(input);		
	}
	return (SUCCESS);
}


t_bool	heredoc_redir(t_list **limlist, t_redir *redir, t_env *env, int *exit_status)
{
	int	success;
	int fd;

	fd = open(redir->str, O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (FAILURE);
	success = heredoc_scan(redir->type, (*limlist)->content, fd, env, exit_status);
	close(fd);
	*limlist = (*limlist)->content;
	return (success);
}

t_bool	heredoc_redir_loop(t_list **limlist, t_redir *redir, t_env *env, int *exit_status)
{
	int	exit_code;

	exit_code = SUCCESS;
	while (redir)
	{
		if (redir->type & HEREDOC)
		{
			exit_code = heredoc_redir(limlist, redir, env, exit_status);
			if (exit_code != SUCCESS)
				break ;
		}
		redir = redir->next;
	}
	return (exit_code);
}

int	heredoc_child(t_list *limlist, t_cmd_m *cmdlist, t_env_m *env, int *exit_status)
{
	t_bool exit_code;
	t_cmd	*cmd;
	t_list	*currentlim;

	cmd = cmdlist;
	currentlim = limlist;
	exit_code = SUCCESS;
	signal(SIGINT, handler_ctrl_c_heredoc);
	errno = 0;
	while (cmd)
	{
		exit_code = heredoc_redir_loop(&currentlim, cmd->redir, env, exit_status);
		if (exit_code != SUCCESS)
			break ;
		cmd = cmd->next;
	}
	ft_lstclear(&limlist, free);
	pipeline_free(&cmdlist);
	env_free(env);
	exit (exit_code);
}

t_char_m	*new_tempfile(void)
{
	char	*path;
	int 	fd;

	path = get_path_temp();
	if (path == NULL)
		return(NULL);
	fd = open(path, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		free(path);
		return (NULL);
	}
	close(fd);
	return (path);
}

t_list *create_temp_file(t_cmd *cmdlist)
{
	t_redir	*redir;
	t_list	*limlist;

	limlist = NULL;
	while (cmdlist)
	{
		redir =cmdlist->redir;
		while (redir)
		{
			if (redir->type & HEREDOC)
			{
				if(ft_lstadd_back_new(&limlist, redir->str) == FAILURE)
				{
					ft_lstclear(&limlist, free);
					return (NULL);
				}
				redir->str = new_tempfile();
				if (!redir->str)
				{
					ft_lstclear(&limlist, free);
					return (NULL);
				}
			}
			redir = redir->next;
		}
		cmdlist = cmdlist->next;
	}
	return (limlist);
}

t_bool heredoc(t_cmd_m *cmdlist, t_env_m *env, int *exit_status)
{
	int		pid;
	int		wstatus;
	int		exit_code;
	t_list	*limlist;

	errno = 0;
	exit_code = SUCCESS;
	limlist = create_temp_file(cmdlist);
	if (!limlist)
	{
		if (errno)
			exit_on_failure(cmdlist, NULL, NULL, env);
		else
			return (SUCCESS);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		heredoc_child(limlist, cmdlist, env, exit_status);
	if (pid == -1)
	{
		perror("minishell: heredoc: fork");
		return (FAILURE);
	}
	ft_lstclear(&limlist, free);
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		exit_code = WEXITSTATUS(wstatus);
	if (exit_code != SUCCESS)
		*exit_status = exit_code;
	signal(SIGINT, handler_ctrl_c);
	return (exit_code);
}
