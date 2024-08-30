/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:59:01 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 13:51:07 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"

static	t_token_list *delimit_token(t_lexer_state *lexer_state)
{
	while (*lexer_state->end != '\0')
	{
		lexer_state->end++;
	}
	char *token_value = ft_substr(lexer_state->start, 0, lexer_state->end - lexer_state->start);
	lexer_state->start = lexer_state->end;
	return (construct_token(TOKEN_WORD, token_value));
}

static void init_lexer_state(char *string, t_lexer_state *lexer_state)
{
	lexer_state->start = string;
	lexer_state->end = string;
	lexer_state->is_inside_quote = false;
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
		if (one_token != NULL)
			ft_lstadd_back(&token_list, one_token);
		if (*(lexer_state.end) == '\0')
			break;
	}
	return (token_list);
}
