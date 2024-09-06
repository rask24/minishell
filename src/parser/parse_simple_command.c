/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:26:37 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/06 19:29:21 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "token.h"

t_ast	*parse_simple_command(t_token_list *token_list)
{
	t_ast	*ast;

	(void)token_list;
	ast = NULL;
	return (ast);
}
