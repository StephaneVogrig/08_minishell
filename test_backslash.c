/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testbackslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:19:44 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/11 16:30:21 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	write(1, "\"", 1);
	write (1, "\n", 1);
	// while (argc--)
	// {
	// 	write (1, *argv, strlen(*argv));
	// 	write (1, "\n", 1);
	// 	argv++;
	// }
	return (0);
}
