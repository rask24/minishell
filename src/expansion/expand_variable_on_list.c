/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_on_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:37:49 by yliu              #+#    #+#             */
/*   Updated: 2024/10/13 19:12:33 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

t_list	*expand_variable_on_list(t_list *curr, t_ctx *ctx)
{
	t_expand_info	*unexpanded_info;
	t_list			*expanded_tokens;
	t_list			*list;

	list = NULL;
	while (curr)
	{
		unexpanded_info = construct_string_struct(curr->content);
		expanded_tokens = split_by_ifs(unexpanded_info, ctx);
		destroy_string_struct(unexpanded_info);
		ft_lstadd_back(&list, expanded_tokens);
		curr = curr->next;
	}
	return (list);
}
