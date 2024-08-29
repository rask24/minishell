/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:59:01 by yliu              #+#    #+#             */
/*   Updated: 2024/08/29 16:40:16 by yliu             ###   ########.fr       */
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
