/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:15:30 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/06 16:30:11 by smortemo         ###   ########.fr       */
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

char	*hd_temp_name()
{
	int num;
	int i;
	char *hdt;

	num = 2589; //peut etre la valeur de SYSTEMD_EXEC_PID (env)
	i = 0;
	while(1)
	{
		num = mini_rand(num, i);
		hdt = ft_itoa(num);
		if (!hdt)
			exit(0);
		hdt = ft_strjoin_free_s2("/tmp/hdt_", hdt);
		if (!hdt)
			exit(0);
		if (access(hdt, F_OK) == -1)
			return (hdt);
		free(hdt);
		i++;
	}
	return (NULL);
}

int	get_str(char *limiter, int fd_hdt)
{
	char	*str;
	
	while (1)
	{
		str = get_next_line(0); //str = readline(">");
		if (!str)
			return (0);
		str[ft_strlen(str) - 1] = '\0';
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(str) == ft_strlen(limiter))
		{
			free(str);
			close(fd_hdt);
			return (1);
		}
		else
		{
			write(fd_hdt, str, ft_strlen(str));
			write(fd_hdt, "\n", 1);
			free(str);
		}
	}
	close(fd_hdt);
	return (1);
}

int	heredoc_fill(char *limiter)
{
	char *hdt; 
	int fd_hdt;

	hdt = hd_temp_name();
	if (hdt == NULL)
		return(ENOMEM);
	fd_hdt = open(hdt, O_RDWR | O_CREAT, 0644);
	free(hdt);// !! garder pour retrouver le nom du fichier temp
	// Faire une fonction a la fin de la cmd -> unlink(hdt) 
	get_str(limiter, fd_hdt);
	close(fd_hdt);
	return (0);
}

int	heredoc(t_env *env, t_cmd *cmd)
{
	char *limiter;
	int	error;
	// recuperer la valeur du limiter
	error = heredoc_fill(limiter);
	if (error == ENOMEM)
	{
		cmd_free(cmd);//??
		env_free(env);//??
		exit(EXIT_FAILURE);//??
	}
	return (0);
}