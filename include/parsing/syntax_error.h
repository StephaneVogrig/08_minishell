/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:02:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/08 22:49:14 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ERROR_H
# define SYNTAX_ERROR_H

# include "libft.h"
# include "str.h"

#define SYNTAX_ERROR_MSG "minishell: syntax error near unexpected token "

t_bool	syntax_error(char *input);

/* syntax error utils */
t_bool	syntax_error_msg(char c);
char	*syntax_end_quote(char *str);

#endif