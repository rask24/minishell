/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:45:32 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 22:59:48 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

void	process_quote(t_lexer *lexer, char left_quote_char)
{
	lexer->right++;
	while (true)
	{
		if (*lexer->right == '\0')
			ft_printf("Syntax error: quote not closed");
		if (*lexer->right == left_quote_char)
			break ;
		lexer->right++;
	}
	lexer->right++;
}
