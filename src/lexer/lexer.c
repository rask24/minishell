/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:59:01 by yliu              #+#    #+#             */
/*   Updated: 2024/08/30 22:58:23 by yliu             ###   ########.fr       */
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
	construct_lexer((char *)input, &lexer);
	while (true)
	{
		one_token = get_next_token(&lexer);
		ft_lstadd_back(&token_list, one_token);
		if (*(lexer.right) == '\0')
			break ;
	}
	return (token_list);
}
