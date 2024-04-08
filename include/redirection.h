/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 03:33:33 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/08 04:22:18 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <fcntl.h>
# include "libft.h"

enum e_redir_type {REDIR_IN, REDIR_OUT_APD, REDIR_OUT_TRC, HEREDOC};

typedef struct s_redir{
	t_char_m		*file_name;
	int				type;
	struct s_redir	*next;
}	t_redir;

int		is_directory(char *path);
t_bool	redirection_add(t_redir **redirs, t_char_m *file_name, int type);
void	redirection_free(t_redir **redirs);


#endif