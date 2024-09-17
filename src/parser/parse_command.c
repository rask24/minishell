/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 02:19:16 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/17 19:15:48 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

/*
** command  : simple_command
**          : '(' list ')'
**          : '(' list ')' redirect_list
**          ;
*/
t_ast	*parse_command(t_token_list **cur_token)
{
	t_ast	*node;
	t_ast	*tmp;

	if (get_token_type(*cur_token) != TOKEN_L_PARENTHESIS)
		return (parse_simple_command(cur_token));
	consume_token(cur_token);
	tmp = parse_list(cur_token);
	if (tmp == NULL)
		return (NULL);
	node = construct_ast(AST_SUBSHELL, tmp, NULL);
	if (!expect_token(cur_token, TOKEN_R_PARENTHESIS))
		return (handle_error(node, get_token_value(*cur_token)));
	while (is_redirect_token(get_token_type(*cur_token)))
	{
		if (!parse_redirect(node, cur_token))
			return (handle_error(node, get_token_value(*cur_token)));
	}
	return (node);
}
