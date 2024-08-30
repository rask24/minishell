/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:59:01 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 22:41:56 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_internal.h"
#include "token.h"

static bool is_quote_char(char c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

static void process_quote(t_lexer *lexer, char starting_quote_char)
{
	lexer->end++;
	while (true)
	{
		if (*lexer->end == '\0')
			ft_printf("Syntax error: quote not closed");
		if (*lexer->end == starting_quote_char)
			break;
		lexer->end++;
	}
	lexer->end++;
}

static	t_token_list *delimit_token(t_lexer *lexer)
{
	while(true)
	{
		if (*lexer->end == '\0')
		{
			char *token_value = ft_substr(lexer->start, 0, lexer->end - lexer->start);
			lexer->start = lexer->end;
			return (construct_token(TOKEN_WORD, token_value));
		}
		if (is_quote_char(*lexer->end))
			process_quote(lexer, *lexer->end);
		if (ft_isspace(*lexer->end))
			return(process_blank(lexer));
		lexer->end++;
	}
}

t_token_list	*lexer(const char *string)
{
	t_token_list	*one_token;
	t_token_list	*token_list;
	t_lexer  lexer;

	token_list = NULL;
	construct_lexer((char *)string, &lexer);
	while (true)
	{
		one_token = delimit_token(&lexer);
		ft_lstadd_back(&token_list, one_token);
		if (*(lexer.end) == '\0')
			break;
	}
	return (token_list);
}
