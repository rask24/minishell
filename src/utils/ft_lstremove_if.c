/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:07:14 by yliu              #+#    #+#             */
/*   Updated: 2024/09/10 22:42:03 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	ft_lstremove(t_list **lst, t_list *node, void (*del)(void *))
{
	t_list	*prev;

	if (!lst || !*lst || !node || !del)
		return ;
	prev = ft_lst_before(*lst, node);
	if (!prev)
		*lst = node->next;
	else
		prev->next = node->next;
	ft_lstdelone(node, del);
}

void	ft_lstremove_if(t_list **lst, t_pred is_remove, void *param, void (*del)(void *))
{
	t_list	*curr;
	t_list	*next;

	if (!lst || !*lst || !is_remove || !del)
		return ;
	curr = *lst;
	while (curr)
	{
		next = curr->next;
		if (is_remove(curr, param))
			ft_lstremove(lst, curr, del);
		curr = next;
	}
}
