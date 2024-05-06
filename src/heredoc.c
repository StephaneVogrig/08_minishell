/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:15:30 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/06 21:08:21 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"heredoc.h"

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

t_bool	heredoc_fill(char *limiter, int fd)
{
	char	*str;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		str = get_next_line(0); //str = readline(">");
		if (!str)
		{
			fd_printf(STDERR_FD, "minishell: warning: here-document delimited by end-of-file\n");
			return (SUCCESS);
		}
		str[ft_strlen(str) - 1] = '\0';
		if (ft_strncmp(str, limiter, limiter_len) == 0 
			&& ft_strlen(str) == limiter_len)
		{
			free(str);
			return (SUCCESS);
		}
		else
		{
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
			free(str);
		}
	}
	return (FAILURE);
}

t_bool	heredoc(t_redir *redir, t_env *env, int *exit_status)
{
	int	success;
	char *path; 
	int fd;

	(void)env;
	(void)exit_status;
	path = get_path_temp();
	if (path == NULL)
		return(FAILURE);
	fd = open(path, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		free(path);
		return (FAILURE);
	}
	success = heredoc_fill(redir->str, fd);
	close(fd);
	if (!success)
	{
		free(path);
		return (FAILURE);
	}
	free(redir->str);
	redir->str = path;
	return (SUCCESS);
}

t_bool	heredoc_redir(t_redir *redir, t_env *env, int *exit_status)
{
	while (redir)
	{
		if (redir->type & HEREDOC)
			if (heredoc(redir, env, exit_status) == FAILURE)
				return (FAILURE);
		redir = redir->next;
	}
	return (SUCCESS);
}

t_bool	heredoc_pipe(t_cmd_m *pipeline, t_env_m *env, int *exit_status)
{
	errno = 0;
	while (pipeline)
	{
		if (heredoc_redir(pipeline->redir, env, exit_status) == FAILURE)
		{
			pipeline_free(&pipeline);
			if (errno)
				exit_on_failure(NULL, NULL, env);
			return (FAILURE);
		}
		pipeline = pipeline->next;
	}
	return (SUCCESS);
}
