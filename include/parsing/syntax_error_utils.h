/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:43:13 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:56:15 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ERROR_UTILS_H
# define SYNTAX_ERROR_UTILS_H

# include "libft.h"
# include "str.h"

# define SYNTAX_ERROR_MSG "minishell: syntax error near unexpected token "

t_bool	syntax_error_msg(char c);
char	*syntax_end_quote(char *str);

#endif
