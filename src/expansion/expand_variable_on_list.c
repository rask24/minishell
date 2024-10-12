/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_on_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:37:49 by yliu              #+#    #+#             */
/*   Updated: 2024/10/13 00:51:08 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

t_list	*expand_variable_on_list(t_list *curr, t_ctx *ctx)
{
	t_string	*token_content_;
	t_list		*tokens;
	t_list		*list;

	list = NULL;
	while (curr)
	{
		token_content_ = construct_string_struct(curr->content);
		tokens = split_by_ifs(token_content_, ctx);
		destroy_string_struct(token_content_);
		ft_lstadd_back(&list, tokens);
		curr = curr->next;
	}
	return (list);
}
