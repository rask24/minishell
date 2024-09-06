/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:11:50 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/06 19:25:05 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser_internal.h"
#include "token.h"

t_ast	*parser(t_token_list *token_list)
{
	t_ast	*ast;

	(void)token_list;
	ast = NULL;
	return (ast);
}
