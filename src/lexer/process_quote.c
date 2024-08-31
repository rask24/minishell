/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:45:32 by yliu              #+#    #+#             */
/*   Updated: 2024/08/31 14:06:54 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

void	process_quote(t_lexer *lexer, char left_quote_char)
{
	lexer->right++;
	while (*lexer->right != left_quote_char)
	{
		if (*lexer->right == '\0')
			exit(ft_printf("Syntax error: quote not closed"));
		lexer->right++;
	}
}
