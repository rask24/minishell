/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:24:47 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/01 19:26:03 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "utils.h"

t_ast	*construct_ast(t_ast_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	node = ft_xmalloc(sizeof(t_ast));
	node->type = type;
	node->left = left;
	node->right = right;
	node->cmd_args = NULL;
	node->redirects = NULL;
	return (node);
}

t_redirect_info	*construct_redirect_info(t_redirect_type type,
					const char *filename)
{
	t_redirect_info	*info;

	info = ft_xmalloc(sizeof(t_redirect_info));
	info->type = type;
	info->filepath = ft_xstrdup(filename);
	info->heredoc_fd = -1;
	info->heredoc_size = 0;
	info->should_expand = false;
	return (info);
}

t_redirect_info	*construct_heredoc_redirect_info(const char *delimiter,
					int heredoc_fd, size_t heredoc_size, bool should_expand)
{
	t_redirect_info	*info;

	info = construct_redirect_info(REDIRECT_HEREDOC, delimiter);
	info->heredoc_fd = heredoc_fd;
	info->heredoc_size = heredoc_size;
	info->should_expand = should_expand;
	return (info);
}
