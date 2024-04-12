/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:33:33 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/12 12:16:47 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <fcntl.h>
# include "libft.h"

# define REDIR_IN 0
# define REDIR_OUT_APD 1
# define REDIR_OUT_TRC 2
# define HEREDOC_EXPAND 3
# define HEREDOC_NO_EXPAND 4

# define R_IN 1
# define R_OUT 2
# define R_HEREDOC 4
# define R_APPEND 8
# define R_TRUNC 16
# define R_EXPAND 32
# define R_NO_EXPAND 64


typedef struct s_redir{
	t_char_m		*file_name;
	int				type;
	struct s_redir	*next;
}	t_redir;

int		is_directory(char *path);
t_bool	redirection_add(t_redir **redirs, t_char_m *file_name, int type);
void	redirection_free(t_redir **redirs);

#endif