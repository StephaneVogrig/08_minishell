/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_wait.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:18:16 by svogrig           #+#    #+#             */
/*   Updated: 2024/05/28 10:43:34 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef PIPELINE_WAIT_H
# define PIPELINE_WAIT_H

# include <stdlib.h>
# include <sys/wait.h>
# include "command.h"

int	wait_process(t_cmd *cmd);

#endif
