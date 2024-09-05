/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:24:47 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/05 23:47:54 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "utils.h"

t_ast	*construct_ast(t_ast_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*ast;

	ast = ft_xmalloc(sizeof(t_ast));
	ast->type = type;
	ast->left = left;
	ast->right = right;
	ast->cmd_args = NULL;
	ast->redirects = NULL;
	return (ast);
}

t_redirect_info	*construct_redirect_info(t_redirect_type type,
					const char *filename)
{
	t_redirect_info	*info;

	info = ft_xmalloc(sizeof(t_redirect_info));
	info->type = type;
	info->filepath = ft_xstrdup(filename);
	return (info);
}
