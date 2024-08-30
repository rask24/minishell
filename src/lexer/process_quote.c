/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:45:32 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 22:48:46 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

void	process_quote(t_lexer *lexer, char starting_quote_char)
{
	lexer->end++;
	while (true)
	{
		if (*lexer->end == '\0')
			ft_printf("Syntax error: quote not closed");
		if (*lexer->end == starting_quote_char)
			break ;
		lexer->end++;
	}
	lexer->end++;
}
