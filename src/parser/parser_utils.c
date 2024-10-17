/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:55:24 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/17 23:45:54 by reasuke          ###   ########.fr       */
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

t_ast	*handle_syntax_error(t_ast *node, const char *token_value)
{
	if (token_value == NULL)
		token_value = "EOF";
	print_syntax_error(token_value);
	destroy_ast(node);
	return (NULL);
}

bool	destroy_and_return(t_ast *node, t_token_list **cur_token,
			bool is_syntax_error)
{
	if (is_syntax_error)
		print_syntax_error(get_token_value(*cur_token));
	destroy_ast(node);
	return (false);
}
