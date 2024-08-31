/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_eof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:22:45 by yliu              #+#    #+#             */
/*   Updated: 2024/08/31 14:23:45 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

void process_eof(t_lexer *lexer)
{
	if (lexer->left == lexer->right)
	{
		lexer->value = NULL;
		lexer->type = TOKEN_EOF;
	} else {
		lexer->value = ft_substr(lexer->left, 0, lexer->right - lexer->left);
		lexer->type = TOKEN_WORD;
		lexer->left = lexer->right;
	}
}
