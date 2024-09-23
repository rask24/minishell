/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 01:16:49 by yliu              #+#    #+#             */
/*   Updated: 2024/09/24 01:18:29 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstremove(t_list **lst, t_list *node, t_del del)
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
