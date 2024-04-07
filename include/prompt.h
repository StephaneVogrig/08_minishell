/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:50:14 by stephane          #+#    #+#             */
/*   Updated: 2024/04/07 03:53:24 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "libft.h"

# define PROMPT_MINISHELL "\033[33mminishell>\033[0m"
# define PROMPT_HEREDOC ">"

void	prompt_print(void);

#endif
