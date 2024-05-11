/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_wait.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:18:16 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/11 15:20:40 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PIPELINE_WAIT_H
# define PIPELINE_WAIT_H

# include <stdlib.h>
# include <sys/wait.h>

int	wait_process(pid_t *pids);

#endif
