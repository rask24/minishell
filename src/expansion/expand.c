/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:57:48 by yliu              #+#    #+#             */
/*   Updated: 2024/10/05 14:54:04 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_internal.h"

t_list	*expand(t_list *cmd_args, t_ctx *ctx)
{
	t_list	*variable_expanded;
	t_list	*wildcard_expanded;
	t_list	*quotes_expanded;

	variable_expanded = expand_variable_on_list(cmd_args, ctx);
	wildcard_expanded = expand_wildcard_on_list(variable_expanded);
	ft_lstclear(&variable_expanded, free);
	quotes_expanded = expand_quotes_on_list(wildcard_expanded);
	ft_lstclear(&wildcard_expanded, free);
	return (quotes_expanded);
}
