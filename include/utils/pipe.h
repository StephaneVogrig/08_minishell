/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 03:28:21 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/31 16:44:12 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <unistd.h>
# include <stdio.h>

# define READ 0
# define WRITE 1

int	pipe_ms(int fds[2]);

#endif