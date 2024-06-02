/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipeline.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephane <stephane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:26:45 by stephane          #+#    #+#             */
/*   Updated: 2024/06/02 18:51:17 by stephane         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "token.h"
#include "pipeline.h"
#include "redirection.h"

t_cmd	*input_to_pipeline(char *input);