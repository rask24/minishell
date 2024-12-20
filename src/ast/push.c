/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:13:36 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/27 10:23:15 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "utils.h"

void	push_cmd_arg(t_ast *node, char *arg)
{
	if (node->type != AST_COMMAND)
	{
		print_error(__func__, "invalid node type");
		return ;
	}
	ft_lstadd_back(&node->cmd_args, ft_xlstnew(arg));
}

void	push_redirect_info(t_ast *node, t_redirect_info *redirect_info)
{
	if (redirect_info == NULL)
	{
		print_error(__func__, "redirect_info is NULL");
		return ;
	}
	if (node->type != AST_COMMAND && node->type != AST_SUBSHELL)
	{
		print_error(__func__, "invalid node type");
		return ;
	}
	ft_lstadd_back(&node->redirects, ft_lstnew(redirect_info));
}
