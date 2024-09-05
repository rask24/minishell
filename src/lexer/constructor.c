/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:32:36 by yliu              #+#    #+#             */
/*   Updated: 2024/09/05 14:07:28 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

void	construct_lexer(const char *input, t_lexer *lexer)
{
	lexer->left = input;
	lexer->right = input;
	lexer->value = NULL;
	lexer->type = -1;
}
