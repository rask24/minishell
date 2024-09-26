/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:57:48 by yliu              #+#    #+#             */
/*   Updated: 2024/09/26 23:21:16 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_internal.h"

static t_list	*expand_token(t_list *token, t_builtins_ctx *ctx)
{
	t_list	*new_args;
	char	*var_expanded;

	var_expanded = expand_variable(token->content, ctx);
	free(var_expanded);
	new_args = ft_lstnew(var_expanded);
	return (new_args);
}

t_list	*expand(t_list *cmd_args, t_builtins_ctx *ctx)
{
	t_list	*iter;

	iter = cmd_args;
	while (iter)
	{
		ft_lstreplace(&cmd_args, iter, expand_token(iter, ctx));
		iter = iter->next;
	}
	return (cmd_args);
}
