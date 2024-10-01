/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:57:48 by yliu              #+#    #+#             */
/*   Updated: 2024/10/01 19:56:23 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "expansion_internal.h"

static t_list	*expand_token(t_list *token, t_ctx *ctx)
{
	t_list	*result_list;
	char	*var_expanded;
	char	*quote_expanded;
	char	**wildcard_expanded;
	int		i;

	i = 0;
	result_list = NULL;
	var_expanded = expand_variable(token->content, ctx);
	quote_expanded = expand_quotes(var_expanded);
	wildcard_expanded = expand_wildcard(quote_expanded, ctx);
	free(var_expanded);
	free(quote_expanded);
	while (wildcard_expanded[i])
	{
		ft_lstadd_back(&result_list, ft_xlstnew(wildcard_expanded[i]));
		i++;
	}
	ft_free_strs(wildcard_expanded);
	return (result_list);
}

t_list	*expand(t_list *cmd_args, t_ctx *ctx)
{
	t_list	*current;
	t_list	*next;

	current = cmd_args;
	while (current)
	{
		next = current->next;
		ft_lstreplace(&cmd_args, current, expand_token(current, ctx));
		current = next;
	}
	return (cmd_args);
}
