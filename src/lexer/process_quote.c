/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:45:32 by yliu              #+#    #+#             */
/*   Updated: 2024/09/18 20:32:39 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"
#include "utils.h"

t_token_list	*process_quote(t_lexer *lexer)
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
	lexer->right++;
	return (get_next_token(lexer));
}
