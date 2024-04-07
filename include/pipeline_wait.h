/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_wait.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:18:16 by svogrig           #+#    #+#             */
/*   Updated: 2024/04/06 23:25:26 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_WAIT_H
# define PIPELINE_WAIT_H

# include <stdlib.h>
# include <wait.h>

int	wait_process(pid_t *pids, int n);

#endif
