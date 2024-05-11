/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipeline.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:26:45 by stephane          #+#    #+#             */
/*   Updated: 2024/04/29 01:56:26 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "pipeline.h"
#include "redirection.h"

t_cmd	*input_to_pipeline(char *input, t_env *env, int *exit_status);