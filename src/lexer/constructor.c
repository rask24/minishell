/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:32:36 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 22:33:56 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

void init_lexer_state(char *string, t_lexer_state *lexer_state)
{
	lexer_state->start = string;
	lexer_state->end = string;
}
