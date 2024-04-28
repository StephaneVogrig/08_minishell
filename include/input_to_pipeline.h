/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipeline.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:26:45 by stephane          #+#    #+#             */
/*   Updated: 2024/04/27 12:09:19 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "token.h"
#include "pipeline.h"
#include "redirection.h"

t_cmd	*input_to_pipeline(char *input, char **env, int *exit_status);