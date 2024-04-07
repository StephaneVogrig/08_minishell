/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_perror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:00:43 by svogrig           #+#    #+#             */
/*   Updated: 2024/02/09 16:01:09 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	error_perror(char *error_msg)
{
	perror(error_msg);
	return (ERROR);
}