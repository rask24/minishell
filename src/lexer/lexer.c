/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:59:01 by yliu              #+#    #+#             */
/*   Updated: 2024/09/18 20:23:12 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_internal.h"

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
		if (get_token_type(one_token) == TOKEN_EOF)
			break ;
	}
	return (token_list);
}
