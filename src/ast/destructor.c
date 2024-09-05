/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:58:00 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/05 19:13:22 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

static void	_destory_redirect_info(void *content)
{
	t_redirect_info	*info;

	info = (t_redirect_info *)content;
	free((char *)info->filename);
	free(info);
}

void	destroy_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	ft_lstclear(&ast->cmd_args, free);
	ft_lstclear(&ast->redirects, _destory_redirect_info);
	destroy_ast(ast->left);
	destroy_ast(ast->right);
}
