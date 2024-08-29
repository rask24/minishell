/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:59:01 by yliu              #+#    #+#             */
/*   Updated: 2024/08/29 16:52:26 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"

void	ft_xrealloc(t_token_buffer *token_buffer)
{
	char	*new_buffer;

	token_buffer->cap *= 2;
	new_buffer = ft_xmalloc(token_buffer->cap);
	ft_memcpy(new_buffer, token_buffer->str, token_buffer->len);
	free(token_buffer->str);
	token_buffer->str = new_buffer;
	return ;
}

void push_back_char(t_token_buffer *token_buffer, char c)
{
	if (token_buffer->len + 1 == token_buffer->cap)
		ft_xrealloc(token_buffer);
	token_buffer->str[token_buffer->len++] = c;
	token_buffer->str[token_buffer->len] = '\0';
}

t_token_list	*store_to_buffer_statefully(t_token_buffer *token_buffer,
		char c)
{
	push_back_char(token_buffer, c);
	if (token_buffer->len == 2)
	{
		return (construct_token(TOKEN_WORD, ft_strdup(token_buffer->str)));
	}
	return NULL;
}

t_token_list	*lexer(const char *string)
{
	size_t			cursor;
	t_token_list	*one_token;
	t_token_list	*token_list;
	t_token_buffer	token_buffer;

	token_buffer = (t_token_buffer){.str = (char *)ft_xmalloc((size_t)1), .len = 0, .cap = 1};
	cursor = 0;
	token_list = NULL;
	while (string[cursor])
	{
		one_token = store_to_buffer_statefully(&token_buffer, string[cursor]);
		if (one_token != NULL)
		{
			ft_lstadd_back(&token_list, one_token);
		}
		cursor++;
	}
	free(token_buffer.str);
	return (token_list);
}
