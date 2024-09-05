/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:13:36 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/05 18:40:48 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "utils.h"

void	push_cmd_args(t_ast *ast, const char *arg)
{
	if (ast->type != AST_COMMAND)
		print_error(__func__, "invalid node type");
	ft_lstadd_back(&ast->cmd_args, ft_xlstnew(ft_xstrdup(arg)));
}
