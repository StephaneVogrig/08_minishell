/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:33:33 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/18 19:32:07 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <fcntl.h>
# include "libft.h"

# define IN 1
# define OUT 2
# define HEREDOC 4
# define EXPANSE 8
# define APPEND 16
# define UNLINK 32

typedef struct s_redir{
	t_char_m		*str;
	int				type;
	struct s_redir	*next;
}	t_redir;

t_bool	redir_add_str(t_redir **redirs, t_char_m *file_name, int type);
void	redirection_free(t_redir **redirs);

#endif
