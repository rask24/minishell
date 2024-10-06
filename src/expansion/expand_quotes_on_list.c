/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_on_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:28:38 by yliu              #+#    #+#             */
/*   Updated: 2024/10/02 15:28:38 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_internal.h"

t_list	*expand_quotes_on_list(t_list *list)
{
	t_list	*curr;
	t_list	*result;
	char	*wildcard_expanded;

	curr = list;
	result = NULL;
	while (curr)
	{
		wildcard_expanded = expand_quotes(curr->content);
		ft_lstadd_back(&result, ft_xlstnew(wildcard_expanded));
		curr = curr->next;
	}
	ft_lstclear(&list, free);
	return (result);
}
