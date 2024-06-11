/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token_limiter.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:21:24 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/11 14:56:07 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEXT_TOKEN_LIMITER_H
# define NEXT_TOKEN_LIMITER_H

# include "str.h"

char	*next_token_to_limiter(char *input, char **token, t_bool *dequoted);

#endif
