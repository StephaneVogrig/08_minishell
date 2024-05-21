/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:00:33 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/21 18:01:41 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_num(long long num)
{
	int len;

	len = 0;
	if(num < 0)
		len++;
	while(num)
	{
		num = num/10;
		len++;
	}
	return(len);
}

int	len_str_num(char *str)
{
	int len;
	int i;
	
	len = 0;
	i = 0;
	while(str[i])
	{
		if(str[i] == '-')
			len++;
		if(str[i] >= '0' && str[i] <= '9')
			len++;
		i++;
	}
	return(len);
}