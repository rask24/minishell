/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:58:00 by reasuke           #+#    #+#             */
/*   Updated: 2024/10/18 22:59:47 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "libft.h"

static void	destroy_redirect_info(void *content)
{
	t_redirect_info	*info;

	info = (t_redirect_info *)content;
	if (info->heredoc_fd != -1)
		close(info->heredoc_fd);
	free((char *)info->file_or_delim);
	free(info);
}

void	destroy_ast(t_ast *node)
{
	if (node == NULL)
		return ;
	ft_lstclear(&node->cmd_args, free);
	ft_lstclear(&node->redirects, destroy_redirect_info);
	destroy_ast(node->left);
	destroy_ast(node->right);
	free(node);
}
