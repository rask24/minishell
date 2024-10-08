/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yliu <yliu@student.42.jp>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:07:14 by yliu              #+#    #+#             */
/*   Updated: 2024/09/24 01:16:45 by yliu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstremove_if(t_list **lst, t_pred should_remove, void *param,
							t_del del)
{
	t_list	*curr;
	t_list	*next;

	if (!lst || !*lst || !should_remove || !del)
		return ;
	curr = *lst;
	while (curr)
	{
		next = curr->next;
		if (should_remove(curr, param))
			ft_lstremove(lst, curr, del);
		curr = next;
	}
}
