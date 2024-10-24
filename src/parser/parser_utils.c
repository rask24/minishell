/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:55:24 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/24 17:38:04 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

bool	consume_token(t_token_list **cur_token)
{
	if (*cur_token == NULL)
		return (false);
	*cur_token = (*cur_token)->next;
	return (true);
}

t_ast	*handle_parse_status(t_ast *node, t_parse_status status)
{
	if (status == PARSE_FAILURE)
		return (destroy_ast(node));
	else if (status == PARSE_ABORT)
	{
		destroy_ast(node);
		return (construct_ast(AST_ABORT, NULL, NULL));
	}
	return (node);
}
