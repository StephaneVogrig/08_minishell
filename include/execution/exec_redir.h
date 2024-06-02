/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:14:31 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/01 19:06:19 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef EXEC_REDIR_H
# define EXEC_REDIR_H

# include "heredoc.h"
# include "redirection.h"
# include "environment.h"
# include "token.h"
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include "pipeline.h"
// # include "token.h"

t_bool	exec_redir(t_redir *redirs, t_env *env);

#endif