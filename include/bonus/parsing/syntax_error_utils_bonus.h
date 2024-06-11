/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils_bonus.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:24:45 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:47:58 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ERROR_UTILS_BONUS_H
# define SYNTAX_ERROR_UTILS_BONUS_H

# include "tokenlist_bonus.h"
# include "syntax_error_utils.h"
# include "syntax_error_utils_bonus.h"

int		check_parenthesis_close(t_tokenlist	*token, int *lvl_parenthesis);
int		check_semicolon(t_tokenlist	*token);
int		check_control(t_tokenlist	*token);
int		syntax_error_msg_token(t_tokenlist *token);

#endif
