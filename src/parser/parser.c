/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:11:50 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/14 23:30:55 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

t_ast	*parser(t_token_list *token_list)
{
	t_ast			*node;
	t_token_list	**cur_token;

	cur_token = &token_list;
	node = parse_pipeline(cur_token);
	return (node);
}
