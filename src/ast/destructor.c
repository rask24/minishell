/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:58:00 by reasuke           #+#    #+#             */
/*   Updated: 2024/09/05 23:47:54 by reasuke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "libft.h"

static void	_destroy_redirect_info(void *content)
{
	t_redirect_info	*info;

	info = (t_redirect_info *)content;
	free((char *)info->filepath);
	free(info);
}

void	destroy_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	ft_lstclear(&ast->cmd_args, free);
	ft_lstclear(&ast->redirects, _destroy_redirect_info);
	destroy_ast(ast->left);
	destroy_ast(ast->right);
}
