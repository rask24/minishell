/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:45:32 by yliu              #+#    #+#             */
/*   Updated: 2024/09/03 20:13:32 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

void	process_quote(t_lexer *lexer)
{
	char	left_quote_char;

	left_quote_char = *lexer->right;
	lexer->right++;
	while (*lexer->right != left_quote_char)
	{
		if (*lexer->right == '\0')
			print_error("process_quote", "unterminated quote");
		lexer->right++;
	}
}
