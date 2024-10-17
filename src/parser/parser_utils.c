/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:55:24 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/18 00:11:15 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "ast.h"
#include "token.h"
#include "utils.h"

bool	consume_token(t_token_list **cur_token)
{
	if (*cur_token == NULL)
		return (false);
	*cur_token = (*cur_token)->next;
	return (true);
}

bool	expect_token(t_token_list **cur_token, t_token_type type)
{
	if (*cur_token == NULL || get_token_type(*cur_token) != type)
		return (false);
	*cur_token = (*cur_token)->next;
	return (true);
}

t_ast	*abort_parse_syntax_error(t_ast *node, t_token_list **cur_token)
{
	const char	*token_value;

	token_value = get_token_value(*cur_token);
	if (token_value == NULL)
		token_value = "EOF";
	print_syntax_error(token_value);
	destroy_ast(node);
	return (NULL);
}

bool	abort_parse_return(t_ast *node, t_token_list **cur_token,
			bool is_syntax_error)
{
	const char	*token_value;

	token_value = get_token_value(*cur_token);
	if (token_value == NULL)
		token_value = "EOF";
	if (is_syntax_error)
		print_syntax_error(token_value);
	destroy_ast(node);
	return (false);
}
