/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:13:36 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/05 19:36:22 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "utils.h"

void	push_cmd_arg(t_ast *ast, const char *arg)
{
	if (ast->type != AST_COMMAND)
	{
		print_error(__func__, "invalid node type");
		return ;
	}
	ft_lstadd_back(&ast->cmd_args, ft_xlstnew(ft_xstrdup(arg)));
}

void	push_redirect_info(t_ast *ast, t_redirect_info *info)
{
	if (ast->type != AST_COMMAND)
	{
		print_error(__func__, "invalid node type");
		return ;
	}
	ft_lstadd_back(&ast->redirects,
		ft_lstnew(construct_redirect_info(info->type, info->filename)));
}
