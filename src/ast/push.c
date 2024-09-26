/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:13:36 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/26 17:06:59 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "utils.h"

void	push_cmd_arg(t_ast *node, const char *arg)
{
	if (node->type != AST_COMMAND)
	{
		print_error(__func__, "invalid node type");
		return ;
	}
	ft_lstadd_back(&node->cmd_args, ft_xlstnew(ft_xstrdup(arg)));
}

void	push_redirect_info(t_ast *node, t_redirect_info *info)
{
	if (node->type != AST_COMMAND && node->type != AST_SUBSHELL)
	{
		print_error(__func__, "invalid node type");
		return ;
	}
	ft_lstadd_back(&node->redirects,
		ft_lstnew(construct_redirect_info(info->type, info->filepath,
				info->heredoc_fd)));
}
