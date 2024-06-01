/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token_dequoted.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 06:51:01 by svogrig           #+#    #+#             */
/*   Updated: 2024/06/01 13:16:08 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEXT_TOKEN_DEQUOTED_H
# define NEXT_TOKEN_DEQUOTED_H

# include "str.h"

char	*next_token_dequoted(char *input, char **token, t_bool *dequoted);

#endif