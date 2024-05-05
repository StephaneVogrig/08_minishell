/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:15:43 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/06 00:09:09 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "libft.h"
# include "environment.h"
# include "command.h"
# include <limits.h>
# include <errno.h>
// # include <readline/readline.h>
// # include <readline/history.h>

char	*hd_temp_name();
int		heredoc_fill(char *limiter);

#endif