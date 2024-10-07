/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:59:01 by yliu              #+#    #+#             */
/*   Updated: 2024/10/07 18:03:34 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexer_internal.h"
#include "token.h"

t_token_list	*lexer(const char *input)
{
	t_token_list	*one_token;
	t_token_list	*token_list;
	t_lexer			lexer;

	token_list = NULL;
	construct_lexer(input, &lexer);
	while (true)
	{
		one_token = get_next_token(&lexer);
		ft_lstadd_back(&token_list, one_token);
		if (get_token_type(one_token) == TOKEN_EOF
			|| get_token_type(one_token) == TOKEN_UNKNOWN)
			break ;
	}
	return (token_list);
}
