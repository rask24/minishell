/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:18:07 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/17 02:40:07 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

/*
** pipeline  :              command
**           : pipeline '|' command
**           ;
*/
t_ast	*parse_pipeline(t_token_list **cur_token)
{
	t_ast	*node;
	t_ast	*tmp;

	node = parse_command(cur_token);
	if (node == NULL)
		return (NULL);
	while (get_token_type(*cur_token) != TOKEN_EOF)
	{
		if (get_token_type(*cur_token) != TOKEN_PIPE)
			break ;
		consume_token(cur_token);
		tmp = parse_command(cur_token);
		if (tmp == NULL)
			return (NULL);
		node = construct_ast(AST_PIPE, node, tmp);
	}
	return (node);
}
