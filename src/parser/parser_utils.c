/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:55:24 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/18 00:41:33 by reasuke          ###   ########.fr       */
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

// TODO: Replace newline with the more appropriate token value (EOF?)
t_ast	*handle_syntax_error(t_ast *node, const char *token_value)
{
	if (token_value == NULL)
		token_value = "newline";
	print_syntax_error(token_value);
	destroy_ast(node);
	return (NULL);
}
