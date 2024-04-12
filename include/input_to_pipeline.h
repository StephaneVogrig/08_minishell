/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipeline.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:26:45 by stephane          #+#    #+#             */
/*   Updated: 2024/04/12 17:31:00 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "pipeline.h"
#include "redirection.h"
#include "buff.h"
#include "error.h"

t_cmd *input_to_pipeline(char *input, int *error);