/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortemo <smortemo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:50:40 by smortemo          #+#    #+#             */
/*   Updated: 2024/05/05 23:11:55 by smortemo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unitest.h"
#include <limits.h>

// t_bool	hd_temp_available(char *str)
// {
// 	if (access(str, F_OK) == 0)//on genere 1 nouveau nom
// 	{
// 		free(str);
// 		return (FALSE);
// 	}
// 	else
// 		return (TRUE);
// }

// char	*hd_temp_name()
// {
// 	//on genere un nom de fichier
// 	int mod;
// 	int mult;
// 	int num;
// 	int i;
// 	char *hdt;
// 	char	*exist;
	
// 	exist = ft_strdup("/nfs/homes/smortemo/test_temp/777");
// 	mod = 2147483647;
// 	mult = 48271;
// 	num = 12345;
// 	i = 0;
// 	while(hd_temp_available(hdt) && i < 25)
// 	{
// 		if (i == 20)
// 		{		
// 			printf("-> exist %s \n", exist);
// 			if (!hd_temp_available(exist))
// 				return (NULL);
// 		}
//    		num = (mult * num + i) % mod;
// 		if(num < 0)
//             num = -num;
// 		hdt = ft_itoa(num);
// 		hdt = ft_strjoin_free_s2("/nfs/homes/smortemo/test_temp/", hdt);
// 		// hdt = ft_strjoin_free("/tmp/", hdt);
// 		printf("#%d \n", i);
// 		if(hd_temp_available(hdt))
// 			printf("-> %s file does not exist\n", hdt);
// 		i++;
// 	}
// 	return (NULL);
// }


void	heredoc_test()
{
	printf("--------------------------------------------\n");
	printf("TEST heredoc \n");
	printf("--------------------------------------------\n");

	// printf("-> %s \n", hd_temp_name());
	heredoc_fill("limiter");
	
	printf("____________________________________________\n");
	printf("____________________________________________\n");
}