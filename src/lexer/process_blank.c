/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_blank.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:41:59 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 22:42:32 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

static void discard_char(t_lexer *lexer)
{
	lexer->start++;
	lexer->end++;
}

t_token_list *process_blank(t_lexer *lexer)
{
	if (lexer->start == lexer->end)
	{
		discard_char(lexer);
		return (NULL);
	}
	char *token_value = ft_substr(lexer->start, 0, lexer->end - lexer->start);
	while (ft_isspace(*lexer->end))
	{
		lexer->end++;
	}
	lexer->start = lexer->end;
	return (construct_token(TOKEN_WORD, token_value));
}
