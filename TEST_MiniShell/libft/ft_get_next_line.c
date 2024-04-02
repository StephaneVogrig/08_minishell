/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 15:13:14 by smortemo          #+#    #+#             */
/*   Updated: 2024/03/19 15:32:21 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2000000
#endif

static char	*free_line(char *current_line)
{
	free(current_line);
	return (NULL);
}

static int	end_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

static char	*clean_buffer(char *temp, char *current_line, char *buf)
{
	int	start_next_line;

	start_next_line = 0;
	start_next_line = end_line(current_line) + 1;
	ft_strcpy(buf, temp);
	current_line[start_next_line] = '\0';
	return (current_line);
}

static char	*ft_strchr_mod(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return (&str[i + 1]);
		i++;
	}
	return (NULL);
}

char	*ft_get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*current_line;
	char		*temp;
	int			nb_read;

	current_line = NULL;
	nb_read = 1;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	current_line = ft_strdup(buf);
	while (ft_strchr_mod(current_line, '\n') == NULL && nb_read != 0)
	{
		nb_read = read(fd, buf, BUFFER_SIZE);
		if (nb_read == -1)
			return (free_line(current_line));
		buf[nb_read] = '\0';
		current_line = ft_strjoin_free_s1(current_line, buf);
	}
	if (ft_strlen(current_line) == 0)
		return (free_line(current_line));
	temp = ft_strchr_mod(current_line, '\n');
	if (temp != NULL)
		clean_buffer(temp, current_line, buf);
	return (current_line);
}
