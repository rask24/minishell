/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:59:01 by yliu              #+#    #+#             */
/*   Updated: 2024/08/29 16:41:32 by yliu             ###   ########.fr       */
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
