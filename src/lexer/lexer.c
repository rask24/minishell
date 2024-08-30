/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:59:01 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 22:06:11 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"

static bool is_quote_char(char c)
{
	return (c == SINGLE_QUOTE || c == DOUBLE_QUOTE);
}

static void process_quote(t_lexer_state *lexer_state, char starting_quote_char)
{
	lexer_state->end++;
	while (true)
	{
		if (*lexer_state->end == '\0')
			ft_printf("Syntax error: quote not closed");
		if (*lexer_state->end == starting_quote_char)
			break;
		lexer_state->end++;
	}
	lexer_state->end++;
}

static void discard_char(t_lexer_state *lexer_state)
{
	lexer_state->start++;
	lexer_state->end++;
}

static t_token_list *process_blank(t_lexer_state *lexer_state)
{
	if (lexer_state->start == lexer_state->end)
	{
		discard_char(lexer_state);
		return (NULL);
	}
	char *token_value = ft_substr(lexer_state->start, 0, lexer_state->end - lexer_state->start);
	while (ft_isspace(*lexer_state->end))
	{
		lexer_state->end++;
	}
	lexer_state->start = lexer_state->end;
	return (construct_token(TOKEN_WORD, token_value));
}

static	t_token_list *delimit_token(t_lexer_state *lexer_state)
{
	while(true)
	{
		if (*lexer_state->end == '\0')
		{
			char *token_value = ft_substr(lexer_state->start, 0, lexer_state->end - lexer_state->start);
			lexer_state->start = lexer_state->end;
			return (construct_token(TOKEN_WORD, token_value));
		}
		if (is_quote_char(*lexer_state->end))
			process_quote(lexer_state, *lexer_state->end);
		if (ft_isspace(*lexer_state->end))
			return(process_blank(lexer_state));
		lexer_state->end++;
	}
}

static void init_lexer_state(char *string, t_lexer_state *lexer_state)
{
	lexer_state->start = string;
	lexer_state->end = string;
}

t_token_list	*lexer(const char *string)
{
	t_token_list	*one_token;
	t_token_list	*token_list;
	t_lexer_state  lexer_state;

	token_list = NULL;
	init_lexer_state((char *)string, &lexer_state);
	while (true)
	{
		one_token = delimit_token(&lexer_state);
		ft_lstadd_back(&token_list, one_token);
		if (*(lexer_state.end) == '\0')
			break;
	}
	return (token_list);
}
