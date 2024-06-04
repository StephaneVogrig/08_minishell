/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_pipelist.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svogrig <svogrig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:26:45 by stephane          #+#    #+#             */
/*   Updated: 2024/06/04 13:37:29 by svogrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_TO_PIPELINE_H
# define INPUT_TO_PIPELINE_H

# include "token.h"
# include "pipeline.h"
# include "redirection.h"
# include "parse.h"

t_cmd	*input_to_pipelist(char *input);

#endif