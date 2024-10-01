/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:58:00 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/01 12:50:21 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ast.h"
#include "libft.h"

static void	_destroy_redirect_info(void *content)
{
	t_redirect_info	*info;

	info = (t_redirect_info *)content;
	if (info->heredoc_fd != -1)
		close(info->heredoc_fd);
	free((char *)info->filepath);
	free(info);
}

void	destroy_ast(t_ast *node)
{
	if (node == NULL)
		return ;
	ft_lstclear(&node->cmd_args, free);
	ft_lstclear(&node->redirects, _destroy_redirect_info);
	destroy_ast(node->left);
	destroy_ast(node->right);
}
